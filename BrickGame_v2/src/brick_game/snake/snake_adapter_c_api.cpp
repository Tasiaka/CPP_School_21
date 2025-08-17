#include "snake_controller.h"
using s21::SnakeController;

static SnakeController& Controller() {
  static SnakeController c;
  return c;
}

extern "C" {
void userInput(UserAction_t action, bool hold) {
  Controller().UserInput(action, hold);
}
GameInfo_t updateCurrentState() { return Controller().Update(); }
}
