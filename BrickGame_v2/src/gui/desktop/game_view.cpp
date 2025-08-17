#include "game_view.h"

#include <QBrush>
#include <QPainter>
#include <QPen>

namespace s21 {

GameView::GameView(QWidget* parent) : QWidget(parent) {
  setFocusPolicy(Qt::StrongFocus);
}

void GameView::SetSnakeMode(bool snake) {
  snakeMode_ = snake;
  update();
}
void GameView::UpdateFrame(const GameInfo_t& gi) {
  gi_ = gi;
  update();
}

void GameView::paintEvent(QPaintEvent*) {
  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing, false);

  PaintGrid(p);
  if (snakeMode_)
    PaintSnake(p);
  else
    PaintTetris(p);

  if (gi_.pause == 1) PaintBanner(p, "PAUSE");
  if (gi_.pause == 2) PaintBanner(p, "GAME OVER");
  if (snakeMode_ && gi_.level == 10 && gi_.score >= 200)
    PaintBanner(p, "YOU WIN");
}

void GameView::PaintGrid(QPainter& p) {
  int cols = 10, rows = 20;
  int cell = qMin(width() / (cols + 1), height() / (rows + 1));
  int ox = 10, oy = 10;
  QPen pen(Qt::gray);
  p.setPen(pen);
  for (int r = 0; r <= rows; ++r)
    p.drawLine(ox, oy + r * cell, ox + cols * cell, oy + r * cell);
  for (int c = 0; c <= cols; ++c)
    p.drawLine(ox + c * cell, oy, ox + c * cell, oy + rows * cell);
}

void GameView::PaintSnake(QPainter& p) {
  if (!gi_.field) return;
  int cols = 10, rows = 20;
  int cell = qMin(width() / (cols + 1), height() / (rows + 1));
  int ox = 10, oy = 10;

  for (int r = 0; r < rows; ++r)
    for (int c = 0; c < cols; ++c) {
      int v = gi_.field[r][c];
      if (!v) continue;
      QRect rect(ox + c * cell + 1, oy + r * cell + 1, cell - 2, cell - 2);
      if (v == 1)
        p.fillRect(rect, Qt::black);  // тело
      else if (v == 2)
        p.fillRect(rect, Qt::darkRed);  // яблоко
    }
}

void GameView::PaintTetris(QPainter& p) {
  if (!gi_.field) return;
  int cols = 10, rows = 20;
  int cell = qMin(width() / (cols + 1), height() / (rows + 1));
  int ox = 10, oy = 10;

  for (int r = 0; r < rows; ++r)
    for (int c = 0; c < cols; ++c)
      if (gi_.field[r][c]) {
        QRect rect(ox + c * cell + 1, oy + r * cell + 1, cell - 2, cell - 2);
        p.fillRect(rect, Qt::black);
      }
}

void GameView::PaintBanner(QPainter& p, const QString& text) {
  p.setPen(Qt::NoPen);
  p.setBrush(QColor(0, 0, 0, 160));
  int w = width(), h = height();
  p.drawRect(0, h / 2 - 30, w, 60);
  p.setPen(Qt::white);
  p.drawText(0, h / 2 - 30, w, 60, Qt::AlignCenter, text);
}

}  // namespace s21
