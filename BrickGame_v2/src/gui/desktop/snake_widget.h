#ifndef SNAKE_GUI_H
#define SNAKE_GUI_H

#include <QWidget>
#include <QTimer>
#include "../../brick_game/snake/controller.h"


namespace s21 {

class SnakeWidget : public QWidget {
 public:
  explicit SnakeWidget(SnakeController* ctrl, QWidget* parent = nullptr);
  ~SnakeWidget() override;

 protected:
  void paintEvent(QPaintEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;

 private:
  void updateFrame();

  SnakeController* ctrl_;  // контроллер MVC
  GameInfo_t      info_;   // текущее состояние поля
  QTimer*         timer_;  // для тик-таймера
};

}  // namespace s21

#endif
