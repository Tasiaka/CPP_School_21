#include "snake_widget.h"
#include <QPainter>
#include <QKeyEvent>

using s21::SnakeWidget;

SnakeWidget::SnakeWidget(SnakeController* controller, QWidget* parent)
    : QWidget(parent)
    , ctrl_(controller)
    , info_({})
    , timer_(new QTimer(this))
{
  // устанавливаем размер окна (300×400) или подбирайте под себя
  setFixedSize(300, 400);

  // соединяем таймер с нашим слотом onTimeout()
  connect(timer_, &QTimer::timeout, this, &SnakeWidget::onTimeout);
  timer_->start(100);  // тик каждые 100 мс
}

SnakeWidget::~SnakeWidget() = default;

void SnakeWidget::onTimeout() {
  // шаг автомата
  ctrl_->Tick();
  // получаем обновлённое состояние поля
  info_ = ctrl_->GetState();
  // если pause==3 (Terminate), останавливаем таймер
  if (info_.pause == 3) {
    timer_->stop();
  }
  // вызовет paintEvent()
  update();
}

void SnakeWidget::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  int cellW = width()  / 10;
  int cellH = height() / 20;

  // рисуем весь массив field[20][10]
  for (int i = 0; i < 20; ++i) {
    for (int j = 0; j < 10; ++j) {
      if (info_.field[i][j]) {
        painter.fillRect(j*cellW, i*cellH, cellW, cellH, Qt::darkGreen);
      }
    }
  }
}

void SnakeWidget::keyPressEvent(QKeyEvent* e) {
  switch (e->key()) {
    case Qt::Key_Left:  ctrl_->ProcessInput(Left,     false); break;
    case Qt::Key_Right: ctrl_->ProcessInput(Right,    false); break;
    case Qt::Key_Up:    ctrl_->ProcessInput(Up,       false); break;
    case Qt::Key_Down:  ctrl_->ProcessInput(Down,     false); break;
    case Qt::Key_Space: ctrl_->ProcessInput(Action,   true ); break;
    case Qt::Key_S:     ctrl_->ProcessInput(Start,    false); break;
    case Qt::Key_P:     ctrl_->ProcessInput(Pause,    false); break;
    case Qt::Key_T:     ctrl_->ProcessInput(Terminate,false); break;
    default: QWidget::keyPressEvent(e);
  }
}
