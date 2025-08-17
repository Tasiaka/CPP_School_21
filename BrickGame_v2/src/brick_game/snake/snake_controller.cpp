#include "snake_controller.h"
namespace s21 {
SnakeController::SnakeController() : model_(), fsm_(&model_) {}
void SnakeController::UserInput(UserAction_t a, bool hold) {
  fsm_.SetAction(a, hold);
}
GameInfo_t SnakeController::Update() {
  fsm_.Step();
  return fsm_.CurrentInfo();
}
}  // namespace s21
