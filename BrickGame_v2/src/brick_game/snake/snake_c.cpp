#include "../common/brick_game.h"
#include "controller.h"
#include <memory>

static s21::GameController* controller = nullptr;

extern "C" {

void initGame() {
    if (!controller) {
        auto model = std::make_unique<s21::SnakeModel>();
        controller = new s21::GameController(std::move(model));
    }
}

void destroyGame() {
    delete controller;
    controller = nullptr;
}

void userInput(UserAction_t action, bool hold) {
    (void)hold; // Параметр hold не используется
    if (controller) {
        controller->handleUserInput(action);
    }
}

GameInfo_t updateCurrentState() {
    if (controller) {
        return controller->getGameInfo();
    }
    return {nullptr, nullptr, 0, 0, 0, 0, 0};
}

}
