#include "tetris_widget.h"
#include <QPainter>
#include <QKeyEvent>
#include <QFont>


TetrisWidget::TetrisWidget(QWidget *parent)
    : QWidget(parent), timer_(new QTimer(this)) {
  setFixedSize(300, 400);  // Примерный размер
  initGame();

  connect(timer_, &QTimer::timeout, this, &TetrisWidget::updateFrame);
  timer_->start(100);
}

TetrisWidget::~TetrisWidget() {
  destroyGame();
}

void TetrisWidget::updateFrame() {
  game_ = updateCurrentState();
  if (game_.pause == 3) timer_->stop();
  update();  // repaint
}

void TetrisWidget::paintEvent(QPaintEvent *) {
  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing);

  int blockSize = 15;
  for (int i = 0; i < 20; ++i)
    for (int j = 0; j < 10; ++j)
      if (game_.field && game_.field[i][j]) {
        p.setBrush(Qt::darkBlue);
        p.drawRect(j * blockSize + 20, i * blockSize + 20, blockSize - 1, blockSize - 1);
      }

  p.setPen(Qt::black);
  p.setFont(QFont("Monospace", 10));
  p.drawText(180, 50, "SCORE:");
  p.drawText(180, 70, QString::number(game_.score));

  p.drawText(180, 100, "BEST:");
  p.drawText(180, 120, QString::number(game_.high_score));

  if (game_.pause == 1)
    p.drawText(60, 180, "PAUSED");
  else if (game_.pause == 2)
    p.drawText(50, 180, "GAME OVER");
}

void TetrisWidget::keyPressEvent(QKeyEvent *e) {
  switch (e->key()) {
    case Qt::Key_Left: userInput(Left, false); break;
    case Qt::Key_Right: userInput(Right, false); break;
    case Qt::Key_Down: userInput(Down, false); break;
    case Qt::Key_Up:
    case Qt::Key_A: userInput(Action, false); break;
    case Qt::Key_S: userInput(Start, false); break;
    case Qt::Key_P: userInput(Pause, false); break;
    case Qt::Key_T: userInput(Terminate, false); break;
  }
}
