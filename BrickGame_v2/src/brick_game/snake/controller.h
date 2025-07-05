// snakeController.h
#ifndef SNAKECONTROLLER_H
#define SNAKECONTROLLER_H

#include "model.h"
#include "../common/brick_game.h"

namespace s21 {

class SnakeController {
 private:
    SnakeModel* model_;

 public:
    explicit SnakeController(SnakeModel* model);
    ~SnakeController();
    void Start();
    void Step();
    void TurnLeft();
    void TurnRight();
    void SetFast(bool fast);

    
    void ProcessInput(UserAction_t action, bool hold);
    void Tick();                // делает один шаг
    GameInfo_t GetState() const;


};

}  // namespace s21

#endif