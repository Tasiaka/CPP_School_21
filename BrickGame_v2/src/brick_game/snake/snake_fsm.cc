#include "snake_fsm.h"
#include <chrono>

namespace s21 {

static uint64_t NowMs() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

SnakeFSM::SnakeFSM(SnakeModel* model) : model_(model) { }

void SnakeFSM::SetAction(UserAction_t action, bool hold) {
  last_input_ = action;
  hold_ = hold;
  new_input_ = true;
}

int SnakeFSM::NextDeadlineMs() const {
  return (state_ == SnakeState::FastRunning) ? model_->GetFastTickMs() : model_->GetTickMs();
}

bool SnakeFSM::ShouldTick() {
  uint64_t now = NowMs();
  if (last_ms_ == 0) { last_ms_ = now; return false; }
  int need = NextDeadlineMs();
  if (now - last_ms_ >= static_cast<uint64_t>(need)) { last_ms_ = now; return true; }
  return false;
}

void SnakeFSM::Step() {
  switch (state_) {
    case SnakeState::Start:       HandleStart(); break;
    case SnakeState::Running:     HandleRunning(); break;
    case SnakeState::FastRunning: HandleFastRunning(); break;
    case SnakeState::Pause:       HandlePause(); break;
    case SnakeState::Win:         HandleGameOverOrWin(true); break;
    case SnakeState::GameOver:    HandleGameOverOrWin(false); break;
    case SnakeState::Exit:        model_->SetExit(); break;
  }
  new_input_ = false;
}

void SnakeFSM::HandleStart() {
  if (new_input_) {
    if (last_input_ == Start) {
      model_->Reset();
      state_ = SnakeState::Running;
    } else if (last_input_ == Terminate) {
      state_ = SnakeState::Exit;
    }
  }
}

void SnakeFSM::HandleRunning() {
  if (new_input_) {
    if (last_input_ == Pause) { model_->SetPaused(true); state_ = SnakeState::Pause; return; }
    if (last_input_ == Terminate) { state_ = SnakeState::Exit; return; }
    if (last_input_ == Left)  model_->TurnLeft();
    if (last_input_ == Right) model_->TurnRight();
    if (last_input_ == Action && hold_) { model_->SetAccelerate(true); state_ = SnakeState::FastRunning; }
  }
  if (ShouldTick()) model_->Tick();
  if (model_->IsWin()) { state_ = SnakeState::Win; model_->SetPaused(false); return; }
  if (model_->IsGameOver()) { state_ = SnakeState::GameOver; return; }
}

void SnakeFSM::HandleFastRunning() {
  if (new_input_) {
    if (last_input_ == Pause) { model_->SetPaused(true); model_->SetAccelerate(false); state_ = SnakeState::Pause; return; }
    if (last_input_ == Terminate) { state_ = SnakeState::Exit; return; }
    if (last_input_ == Left)  model_->TurnLeft();
    if (last_input_ == Right) model_->TurnRight();
    if (last_input_ == Action && !hold_) { model_->SetAccelerate(false); state_ = SnakeState::Running; }
  }
  if (ShouldTick()) model_->Tick();
  if (model_->IsWin()) { state_ = SnakeState::Win; model_->SetAccelerate(false); return; }
  if (model_->IsGameOver()) { state_ = SnakeState::GameOver; return; }
}

void SnakeFSM::HandlePause() {
  if (new_input_) {
    if (last_input_ == Pause) { model_->SetPaused(false); state_ = SnakeState::Running; }
    if (last_input_ == Terminate) { state_ = SnakeState::Exit; }
  }
}

void SnakeFSM::HandleGameOverOrWin(bool) {
  model_->SetAccelerate(false);  
  model_->SetGameOver();
  if (new_input_) {
    if (last_input_ == Start) { model_->Reset(); state_ = SnakeState::Running; }
    if (last_input_ == Terminate) { state_ = SnakeState::Exit; }
  }
}


}
