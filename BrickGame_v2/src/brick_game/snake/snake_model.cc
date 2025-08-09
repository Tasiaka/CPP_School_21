#include "snake_model.h"
#include <algorithm>
#include <chrono>
#include <fstream>

namespace s21 {

namespace {
constexpr const char* kHighScoreFile   = "BestScore_Snake";
}

SnakeModel::SnakeModel() : rng_(std::random_device{}()) { InitFieldBuffers(); Reset(); }
SnakeModel::~SnakeModel() {
  if (field_) {
    for (int i = 0; i < kRows; ++i) delete[] field_[i];
    delete[] field_;
  }
  if (next_) {
    for (int i = 0; i < 2; ++i) delete[] next_[i];
    delete[] next_;
  }
}

void SnakeModel::InitFieldBuffers() {
  field_ = new int*[kRows];
  for (int i = 0; i < kRows; ++i) field_[i] = new int[kCols] {};
  next_ = new int*[2];
  for (int i = 0; i < 2; ++i) next_[i] = new int[4] {};  // пустая “NEXT” панель (совместимость)
}

void SnakeModel::ClearField() {
  for (int r = 0; r < kRows; ++r)
    for (int c = 0; c < kCols; ++c) field_[r][c] = 0;
}

void SnakeModel::Reset() {
  score_ = 0;
  game_over_ = false;
  pause_code_ = 0;
  level_ = 1;
  dir_ = Direction::Right;
  dir_next_ = Direction::Right;
  turned_this_tick_ = false;
  snake_.clear();
  ClearField();

  std::ifstream in(kHighScoreFile);
  if (in) in >> high_score_;

  PlaceInitialSnake();
  PlaceApple();
}

void SnakeModel::PlaceInitialSnake() {

  int r = kRows / 2;
  int c = kCols / 4;
  snake_.push_back({r, c + 3});
  snake_.push_back({r, c + 2});
  snake_.push_back({r, c + 1});
  snake_.push_back({r, c + 0});
  for (auto& s : snake_) field_[s.r][s.c] = 1;
}

void SnakeModel::PlaceApple() {
  std::uniform_int_distribution<int> dr(0, kRows - 1);
  std::uniform_int_distribution<int> dc(0, kCols - 1);
  while (true) {
    Cell p{dr(rng_), dc(rng_)};
    bool busy = false;
    for (auto& s : snake_) if (s.r == p.r && s.c == p.c) { busy = true; break; }
    if (!busy) { apple_ = p; field_[apple_.r][apple_.c] = 2; break; }
  }
}

int SnakeModel::GetTickMs() const {
  int base = 400;             
  int step = 20;            
  int ms = base - (level_ - 1) * step;
  if (ms < 60) ms = 60;
  return ms;
}

int SnakeModel::GetFastTickMs() const {
  int ms = GetTickMs() / 3;
  if (ms < 25) ms = 25;
  return ms;
}


void SnakeModel::TurnLeft() {
  if (turned_this_tick_) return;                   
  Direction cand = LeftOf(dir_);                     
  if (snake_.size() > 1 && cand == OppositeOf(dir_)) 
    return;
  dir_next_ = cand;
  turned_this_tick_ = true;
}

void SnakeModel::TurnRight() {
  if (turned_this_tick_) return;
  Direction cand = RightOf(dir_);
  if (snake_.size() > 1 && cand == OppositeOf(dir_))
    return;
  dir_next_ = cand;
  turned_this_tick_ = true;
}


void SnakeModel::SetAccelerate(bool on) { accelerated_ = on; }

Direction SnakeModel::LeftOf(Direction d) const {
  switch (d) {
    case Direction::Up:    return Direction::Left;
    case Direction::Left:  return Direction::Down;
    case Direction::Down:  return Direction::Right;
    case Direction::Right: return Direction::Up;
  }
  return Direction::Right;
}
Direction SnakeModel::RightOf(Direction d) const {
  switch (d) {
    case Direction::Up:    return Direction::Right;
    case Direction::Right: return Direction::Down;
    case Direction::Down:  return Direction::Left;
    case Direction::Left:  return Direction::Up;
  }
  return Direction::Right;
}

bool SnakeModel::Collides(const Cell& h) const {
  if (h.r < 0 || h.r >= kRows || h.c < 0 || h.c >= kCols) return true;  // стена
  for (size_t i = 0; i < snake_.size(); ++i) {
    if (h.r == snake_[i].r && h.c == snake_[i].c) return true;          // самосъедание
  }
  return false;
}

bool SnakeModel::StepForward() {
  Cell head = snake_.front();
  switch (dir_) {
    case Direction::Up:    head.r -= 1; break;
    case Direction::Right: head.c += 1; break;
    case Direction::Down:  head.r += 1; break;
    case Direction::Left:  head.c -= 1; break;
  }
  if (Collides(head)) { SetGameOver(); return false; }

  bool ate = (head.r == apple_.r && head.c == apple_.c);

  snake_.push_front(head);
  field_[head.r][head.c] = 1;

  if (!ate) {
    auto tail = snake_.back();
    snake_.pop_back();
    field_[tail.r][tail.c] = 0;
  } else {
    score_ += 1;
    int new_level = std::min(10, 1 + score_ / 5);
    level_ = new_level;
    field_[apple_.r][apple_.c] = 1;  // превращается в часть змейки
    PlaceApple();
  }
  SaveHighScoreIfNeeded();
  return ate;
}

void SnakeModel::SaveHighScoreIfNeeded() {
  if (score_ > high_score_) {
    high_score_ = score_;
    std::ofstream out(kHighScoreFile, std::ios::trunc);
    if (out) out << high_score_;
  }
}

void SnakeModel::Tick() {
  if (pause_code_ != 0 || game_over_) return;
  dir_ = dir_next_;
  StepForward();
  turned_this_tick_ = false;
}


void SnakeModel::CopyToGameInfo(GameInfo_t& out) const {
  out.field = field_;
  out.next = next_;
  out.score = score_;
  out.high_score = high_score_;
  out.level = level_;
  out.speed = accelerated_ ? GetFastTickMs() : GetTickMs();
  out.pause = pause_code_;
}

Direction SnakeModel::OppositeOf(Direction d) const {
  switch (d) {
    case Direction::Up:    return Direction::Down;
    case Direction::Down:  return Direction::Up;
    case Direction::Left:  return Direction::Right;
    case Direction::Right: return Direction::Left;
  }
  return Direction::Right;
}
}
