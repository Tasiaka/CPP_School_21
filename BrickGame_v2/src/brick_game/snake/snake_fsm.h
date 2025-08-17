#ifndef SNAKE_FSM
#define SNAKE_FSM

#include <cstdint>

#include "snake_model.h"

namespace s21 {

enum class SnakeState {
  Start,
  Running,
  FastRunning,
  Pause,
  Win,
  GameOver,
  Exit
};

class SnakeFSM {
 public:
  explicit SnakeFSM(SnakeModel* model);

  void SetAction(UserAction_t action, bool hold);
  void Step();

  GameInfo_t CurrentInfo() const {
    GameInfo_t gi{};
    model_->CopyToGameInfo(gi);
    return gi;
  }

 private:
  void HandleStart();
  void HandleRunning();
  void HandleFastRunning();
  void HandlePause();
  void HandleGameOverOrWin(bool is_win);

  int NextDeadlineMs() const;
  bool ShouldTick();

 private:
  SnakeModel* model_;
  SnakeState state_{SnakeState::Start};
  UserAction_t last_input_{Start};
  bool new_input_{false};
  bool hold_{false};

  uint64_t last_ms_{0};
};

}  // namespace s21

#endif