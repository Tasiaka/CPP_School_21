#include "next_view.h"

#include <QPainter>

namespace s21 {

NextView::NextView(QWidget* parent) : QWidget(parent) {
  setMinimumSize(120, 60);
}

void NextView::UpdateNext(const GameInfo_t& gi) {
  gi_ = gi;
  update();
}

void NextView::paintEvent(QPaintEvent*) {
  if (!gi_.next) return;
  QPainter p(this);
  int cell = qMin(width() / 8, height() / 3);
  int ox = (width() - 8 * cell) / 2 + cell;  // центр на 4 колонки
  int oy = (height() - 2 * cell) / 2;

  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 4; ++j)
      if (gi_.next[i][j] == 1) {
        QRect r(ox + j * 2 * cell + 1, oy + i * cell + 1, 2 * cell - 2,
                cell - 2);
        p.fillRect(r, Qt::black);
      }
}

}  // namespace s21