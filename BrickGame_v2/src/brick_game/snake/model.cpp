#include "model.h"
#include <algorithm>
#include <random>
#include <chrono>

namespace s21 {

SnakeModel::SnakeModel() {
    field_ = std::vector<std::vector<int>>(20, std::vector<int>(10, 0));
    Reset();
}

void SnakeModel::Reset() {
    for (auto& row : field_) std::fill(row.begin(), row.end(), 0);
    snake_.clear();
    for (int i = 0; i < 4; i++) snake_.push_back({10, 4 + i});
    dir_ = LEFT;
    score_ = 0;
    state_ = WAITING;
    fast_ = false;
    PlaceApple();
}

void SnakeModel::PlaceApple() {
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    while (true) {
        Coord pos = { static_cast<int>(rng() % 20), static_cast<int>(rng() % 10) };
        if (std::find(snake_.begin(), snake_.end(), pos) == snake_.end()) {
            apple_ = pos;
            break;
        }
    }
}

bool SnakeModel::Collides(const Coord& pos) const {
    return pos.x < 0 || pos.y < 0 || pos.x >= 20 || pos.y >= 10 ||
           std::find(snake_.begin(), snake_.end(), pos) != snake_.end();
}

void SnakeModel::Step() {
    if (state_ == WAITING) state_ = RUNNING;
    if (state_ != RUNNING) return;

    Coord head = snake_.front();
    switch (dir_) {
        case UP:    head.x--; break;
        case DOWN:  head.x++; break;
        case LEFT:  head.y--; break;
        case RIGHT: head.y++; break;
    }
    if (Collides(head)) {
        state_ = LOSE;
        return;
    }
    snake_.push_front(head);
    if (head == apple_) {
        score_ += 10;
        if (snake_.size() == 200) state_ = WIN;
        else PlaceApple();
    } else {
        snake_.pop_back();
    }
}

void SnakeModel::TurnLeft() {
    if (state_ != RUNNING) return;
    if (dir_ == UP) dir_ = LEFT;
    else if (dir_ == DOWN) dir_ = RIGHT;
    else if (dir_ == LEFT) dir_ = DOWN;
    else if (dir_ == RIGHT) dir_ = UP;
}

void SnakeModel::TurnRight() {
    if (state_ != RUNNING) return;
    if (dir_ == UP) dir_ = RIGHT;
    else if (dir_ == DOWN) dir_ = LEFT;
    else if (dir_ == LEFT) dir_ = UP;
    else if (dir_ == RIGHT) dir_ = DOWN;
}

void SnakeModel::SetFast(bool fast) {
    fast_ = fast;
}

SnakeState SnakeModel::GetState() const {
    return state_;
}

std::vector<std::vector<int>>& SnakeModel::GetField() {
    for (auto& row : field_) {
        std::fill(row.begin(), row.end(), 0);
    }
    for (auto& seg : snake_) field_[seg.x][seg.y] = 1;
    field_[apple_.x][apple_.y] = 2;
    return field_;
}

int SnakeModel::GetScore() const {
    return score_;
}

}  // namespace s21
