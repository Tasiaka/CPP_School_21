// snakeController.cpp
#include "controller.h"

namespace s21 {

SnakeController::SnakeController(SnakeModel* model) : model_(model) {}

void SnakeController::Start() {
    model_->Reset();
}

void SnakeController::Step() {
    model_->Step();
}

void SnakeController::TurnLeft() {
    model_->TurnLeft();
}

void SnakeController::TurnRight() {
    model_->TurnRight();
}

void SnakeController::SetFast(bool fast) {
    model_->SetFast(fast);
}

const std::vector<std::vector<int>>& SnakeController::GetField() const {
    return model_->GetField();
}

SnakeState SnakeController::GetState() const {
    return model_->GetState();
}

int SnakeController::GetScore() const {
    return model_->GetScore();
}

}  // namespace s21
