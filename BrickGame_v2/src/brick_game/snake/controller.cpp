#include "controller.h"
namespace s21 {
GameController::GameController(std::unique_ptr<SnakeModel> model) : model_(std::move(model)) {
    allocateField(&game_info_.field, 20, 10);
    allocateField(&game_info_.next, 4, 4);
}
GameController::~GameController() {
    freeField(&game_info_.field, 20);
    freeField(&game_info_.next, 4);
}
void GameController::handleUserInput(UserAction_t a) {
    switch (a) {
        case Start: model_->startGame(); break;
        case Pause: model_->togglePause(); break;
        case Terminate: model_->restartGame(); break;
        case Left: model_->setDirection(Direction::Left); break;
        case Right: model_->setDirection(Direction::Right); break;
        case Up: model_->setDirection(Direction::Up); break;
        case Down: model_->setDirection(Direction::Down); break;
        default: break;
    }
}
void GameController::updateModel() { model_->update(); }
GameInfo_t GameController::getGameInfo() {
    updateModel();
    game_info_.score = model_->getScore();
    game_info_.high_score = model_->getHighScore();
    game_info_.level = model_->getLevel();
    auto state = model_->getState();
    game_info_.pause = (state == GameState::Pause || state == GameState::GameOver);
    copyField(game_info_.field);
    return game_info_;
}
void GameController::copyField(int** dest) {
    for(int i = 0; i < 20; ++i) for(int j = 0; j < 10; ++j) dest[i][j] = 0;
    if (model_->getState() == GameState::StartScreen || model_->getState() == GameState::GameOver) return;
    for (const auto& s : model_->getSnake()) {
        if (s.y >= 0 && s.y < 20 && s.x >= 0 && s.x < 10) dest[s.y][s.x] = 1;
    }
    Point apple = model_->getApple();
    if (apple.y >= 0 && apple.y < 20 && apple.x >= 0 && apple.x < 10) dest[apple.y][apple.x] = 1;
}
void GameController::allocateField(int*** f, int r, int c) {
    *f = new int*[r]; for(int i = 0; i < r; ++i) (*f)[i] = new int[c]();
}
void GameController::freeField(int*** f, int r) {
    if (*f) {
        for(int i = 0; i < r; ++i) if ((*f)[i]) delete[] (*f)[i];
        delete[] *f; *f = nullptr;
    }
}
}