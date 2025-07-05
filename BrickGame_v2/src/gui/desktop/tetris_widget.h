#ifndef TETRIS_WIDGET_H
#define TETRIS_WIDGET_H

#include <QWidget>
#include <QTimer>
#include "../../brick_game/common/brick_game.h"


class TetrisWidget : public QWidget {

 public:
  explicit TetrisWidget(QWidget *parent = nullptr);
  ~TetrisWidget();

 protected:
  void paintEvent(QPaintEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;

 private slots:
  void updateFrame();

 private:
  QTimer *timer_;
  GameInfo_t game_;
};

#endif  // TETRIS_WIDGET_H
