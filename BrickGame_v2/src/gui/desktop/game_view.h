#ifndef GAME_VIEW
#define GAME_VIEW

#include <QWidget>

#include "../../brick_game/common/common.h"

namespace s21 {

class GameView : public QWidget {
 public:
  explicit GameView(QWidget* parent = nullptr);
  void UpdateFrame(const GameInfo_t& gi);
  void SetSnakeMode(bool snake);

 protected:
  void paintEvent(QPaintEvent*) override;
  QSize sizeHint() const override { return {440, 440}; }

 private:
  void PaintSnake(QPainter& p);
  void PaintTetris(QPainter& p);
  void PaintGrid(QPainter& p);
  void PaintBanner(QPainter& p, const QString& text);

 private:
  GameInfo_t gi_{};
  bool snakeMode_{true};
};

}  // namespace s21

#endif