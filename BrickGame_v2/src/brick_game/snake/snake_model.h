#ifndef SNAKE_MODEL
#define SNAKE_MODEL

#include <deque>
#include <random>
#include <utility>

#include "../common/common.h"
namespace s21 {

struct Cell {
  int r{};
  int c{};
};

enum class Direction { Up, Right, Down, Left };

class SnakeModel {
 public:
  SnakeModel();
  ~SnakeModel();

  void Reset();
  void TurnLeft();
  void TurnRight();
  void SetAccelerate(bool on);
  void Tick();
  void CopyToGameInfo(GameInfo_t& out) const;

  int GetScore() const { return score_; }
  int GetHighScore() const { return high_score_; }
  int GetLevel() const { return level_; }
  int GetPauseCode() const { return pause_code_; }

  bool IsGameOver() const { return game_over_; }
  bool IsWin() const { return static_cast<int>(snake_.size()) >= 200; }

  static constexpr int kRows = 20;
  static constexpr int kCols = 10;

  int GetTickMs() const;
  int GetFastTickMs() const;

  void SetPaused(bool p) { pause_code_ = p ? 1 : 0; }
  void SetGameOver() {
    pause_code_ = 2;
    game_over_ = true;
  }
  void SetExit() { pause_code_ = 3; }

  void SetHighScore(int hs) { high_score_ = hs; }
  void SaveHighScoreIfNeeded();

 private:
  void InitFieldBuffers();
  void ClearField();
  void PlaceInitialSnake();
  void PlaceApple();
  bool StepForward();
  bool Collides(const Cell& head) const;
  Direction LeftOf(Direction d) const;
  Direction RightOf(Direction d) const;
  Direction OppositeOf(Direction d) const;

 private:
  int** field_{nullptr};
  int** next_{nullptr};

  std::deque<Cell> snake_;
  Direction dir_{Direction::Right};
  Direction dir_next_{Direction::Right};
  bool turned_this_tick_{false};
  Cell apple_{};
  bool accelerated_{false};

  int score_{0};
  int high_score_{0};
  int level_{1};
  bool game_over_{false};

  int pause_code_{0};

  mutable std::mt19937 rng_;
};

}  // namespace s21

#endif