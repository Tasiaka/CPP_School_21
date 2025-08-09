#ifndef SRC_BRICK_GAME_SNAKE_MODEL_H_
#define SRC_BRICK_GAME_SNAKE_MODEL_H_

#include <list>
#include "../common/brick_game.h"

namespace s21 {

enum class Direction { Up, Down, Left, Right };
enum class GameState { StartScreen, Spawning, Moving, AppleEaten, Collision, Pause, GameOver };

struct Point {
    int x, y;
    bool operator==(const Point& other) const { return x == other.x && y == other.y; }
};

class SnakeModel {
public:
    SnakeModel();
    void update();
    GameState getState() const;
    const std::list<Point>& getSnake() const;
    Point getApple() const;
    int getScore() const;
    int getHighScore() const;
    int getLevel() const;
    void setDirection(Direction new_direction);
    void togglePause();
    void startGame();
    void restartGame();

private:
    void performStateAction();
    void stateAction_Spawning();
    void stateAction_AppleEaten();
    void stateAction_Collision();
    void initGame();
    void moveSnake();
    void spawnApple();
    bool checkCollision();

    GameState state_;
    Direction direction_;
    std::list<Point> snake_;
    Point apple_;
    int score_, high_score_, level_, speed_ms_;
    long long last_update_time_;
    const int width_ = 10, height_ = 20;
};

}
#endif
