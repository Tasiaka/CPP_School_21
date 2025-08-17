#ifndef GAME_WINDOW
#define GAME_WINDOW

#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>

#include "../../brick_game/common/common.h"
#include "../cli/cli_hub.h"
#include "game_view.h"
#include "next_view.h"

namespace s21 {

class GameWindow : public QMainWindow {
 public:
  explicit GameWindow(QWidget* parent = nullptr);
  ~GameWindow() override = default;

 protected:
  void keyPressEvent(QKeyEvent* e) override;
  void keyReleaseEvent(QKeyEvent* e) override;

 private:
  void OnTick();
  void OnSelectSnake();
  void OnSelectTetris();

 private:
  void BuildUi();
  void UpdateHud(const GameInfo_t& gi);
  void UpdateTimerInterval(int ms);
  void ResetActionHold();

 private:
  QWidget* central_{nullptr};
  GameView* view_{nullptr};
  NextView* next_{nullptr};

  QLabel* gameName_{nullptr};
  QLabel* score_{nullptr};
  QLabel* best_{nullptr};
  QLabel* level_{nullptr};
  QLabel* speed_{nullptr};
  QLabel* hint1_{nullptr};
  QLabel* hint2_{nullptr};
  QLabel* hint3_{nullptr};

  QPushButton* btnSnake_{nullptr};
  QPushButton* btnTetris_{nullptr};

  QTimer tick_;
  bool actionHold_{false};  // Space hold для змейки
};

}  // namespace s21

#endif