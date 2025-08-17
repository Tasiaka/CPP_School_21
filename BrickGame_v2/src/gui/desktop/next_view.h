#ifndef NEXT_VIEW
#define NEXT_VIEW

#include <QWidget>

#include "../../brick_game/common/common.h"

namespace s21 {

class NextView : public QWidget {
 public:
  explicit NextView(QWidget* parent = nullptr);
  void UpdateNext(const GameInfo_t& gi);

 protected:
  void paintEvent(QPaintEvent*) override;
  QSize sizeHint() const override { return {140, 80}; }

 private:
  GameInfo_t gi_{};
};

}  // namespace s21

#endif