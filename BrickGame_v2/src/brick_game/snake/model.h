// snakeModel.h
#ifndef SNAKEMODEL_H
#define SNAKEMODEL_H

#include <deque>
#include <vector>

namespace s21 {

struct Coord {
    int x, y;
    bool operator==(const Coord& other) const { return x == other.x && y == other.y; }
};

enum Direction { UP, RIGHT, DOWN, LEFT };
enum SnakeState { WAITING, RUNNING, WIN, LOSE };

class SnakeModel {
 public:
    SnakeModel();
    void Reset();
    void Step();
    void TurnLeft();
    void TurnRight();
    void SetFast(bool fast);

    SnakeState GetState() const;
    std::vector<std::vector<int>>& GetField();
    int GetScore() const;

 private:
    void PlaceApple();
    bool Collides(const Coord& pos) const;

 private:
    std::deque<Coord> snake_;
    Coord apple_;
    Direction dir_;
    SnakeState state_;
    std::vector<std::vector<int>> field_;
    int score_ = 0;
    bool fast_ = false;
};

}  // namespace s21

#endif
