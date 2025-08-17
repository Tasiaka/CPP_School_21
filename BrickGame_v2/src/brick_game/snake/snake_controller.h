#ifndef SNAKE_CONTROLLER
#define SNAKE_CONTROLLER

#include "snake_fsm.h"

namespace s21 {
class SnakeController {
 public:
  SnakeController();
  void UserInput(UserAction_t action, bool hold);
  GameInfo_t Update();

 private:
  SnakeModel model_;
  SnakeFSM fsm_;
};
}  // namespace s21

#endif