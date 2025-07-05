#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>

#include "tetris_widget.h"
#include "snake_widget.h"

#include "../../brick_game/common/brick_game.h"
#include "../../brick_game/snake/controller.h"
#include "../../brick_game/snake/model.h"

class MainWindow : public QMainWindow {

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

 private slots:
  void showTetris();
  void showSnake();

 private:
  QStackedWidget *stack_;
  QPushButton    *btn_tetris_;
  QPushButton    *btn_snake_;
  QWidget        *menu_;
};

#endif  // MAIN_WINDOW_H
