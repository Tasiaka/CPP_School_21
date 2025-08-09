#include "model.h"
#include <chrono>
#include <random>

namespace s21 {

SnakeModel::SnakeModel() { initGame(); high_score_ = 0; }
void SnakeModel::initGame() {
    state_ = GameState::StartScreen; score_ = 0; level_ = 1;
    speed_ms_ = 500; last_update_time_ = 0;
}
void SnakeModel::startGame() {
    if (state_ == GameState::StartScreen || state_ == GameState::GameOver) {
        state_ = GameState::Spawning;
    }
}
void SnakeModel::restartGame() { initGame(); startGame(); }
void SnakeModel::update() {
    auto current_time = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
    if (state_ == GameState::Moving && (current_time - last_update_time_ > speed_ms_)) {
        moveSnake();
        if (checkCollision()) { state_ = GameState::Collision; }
        else if (snake_.front() == apple_) { state_ = GameState::AppleEaten; }
        last_update_time_ = current_time;
    }
    performStateAction();
}
void SnakeModel::performStateAction() {
    switch(state_) {
        case GameState::Spawning: stateAction_Spawning(); break;
        case GameState::AppleEaten: stateAction_AppleEaten(); break;
        case GameState::Collision: stateAction_Collision(); break;
        default: break;
    }
}
void SnakeModel::stateAction_Spawning() {
    snake_.clear();
    snake_.push_front({width_ / 2, height_ / 2});
    snake_.push_front({width_ / 2, height_ / 2 - 1});
    direction_ = Direction::Down;
    spawnApple();
    state_ = GameState::Moving;
    last_update_time_ = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
}
void SnakeModel::stateAction_AppleEaten() {
    score_ += 10;
    if (score_ > high_score_) high_score_ = score_;
    spawnApple();
    state_ = GameState::Moving;
}
void SnakeModel::stateAction_Collision() { state_ = GameState::GameOver; }
void SnakeModel::moveSnake() {
    Point new_head = snake_.front();
    switch (direction_) {
        case Direction::Up: new_head.y--; break;
        case Direction::Down: new_head.y++; break;
        case Direction::Left: new_head.x--; break;
        case Direction::Right: new_head.x++; break;
    }
    snake_.push_front(new_head);
    if (new_head == apple_) {} else { snake_.pop_back(); }
}
bool SnakeModel::checkCollision() {
    Point head = snake_.front();
    if (head.x < 0 || head.x >= width_ || head.y < 0 || head.y >= height_) return true;
    auto it = snake_.begin(); std::advance(it, 1);
    for (; it != snake_.end(); ++it) { if (head == *it) return true; }
    return false;
}
void SnakeModel::spawnApple() {
    std::random_device rd; std::mt19937 gen(rd());
    std::uniform_int_distribution<> dx(0, width_ - 1);
    std::uniform_int_distribution<> dy(0, height_ - 1);
    bool on_snake;
    do {
        on_snake = false; apple_ = {dx(gen), dy(gen)};
        for(const auto& s : snake_) { if (apple_ == s) { on_snake = true; break; } }
    } while (on_snake);
}
void SnakeModel::setDirection(Direction d) {
    if ((direction_ == Direction::Up && d == Direction::Down) ||
        (direction_ == Direction::Down && d == Direction::Up) ||
        (direction_ == Direction::Left && d == Direction::Right) ||
        (direction_ == Direction::Right && d == Direction::Left)) return;
    direction_ = d;
}
void SnakeModel::togglePause() {
    if(state_ == GameState::Moving) { state_ = GameState::Pause; }
    else if (state_ == GameState::Pause) { state_ = GameState::Moving; }
}
GameState SnakeModel::getState() const { return state_; }
const std::list<Point>& SnakeModel::getSnake() const { return snake_; }
Point SnakeModel::getApple() const { return apple_; }
int SnakeModel::getScore() const { return score_; }
int SnakeModel::getHighScore() const { return high_score_; }
int SnakeModel::getLevel() const { return level_; }
}