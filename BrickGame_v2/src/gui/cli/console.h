// consoleView.h
#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H

#include "snakeController.h"
#include <string>

namespace s21 {

enum SnakeMenu {
    START = 1,
    STEP = 2,
    LEFT = 3,
    RIGHT = 4,
    FAST = 5,
    SCORE = 6,
    QUIT = 0
};

class ConsoleView {
 private:
    SnakeController* controller_;

 public:
    explicit ConsoleView(SnakeController* ctrl);
    void PrintMenu();
    int AskChoice();
    void PrintField();
    void StartLoop();
};

}  // namespace s21

#endif
