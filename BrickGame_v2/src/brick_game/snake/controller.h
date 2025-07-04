#ifndef SRC_BRICK_GAME_SNAKE_CONTROLLER_H_
#define SRC_BRICK_GAME_SNAKE_CONTROLLER_H_
#include "model.h"
#include <memory>
namespace s21 {
class GameController {
public:
    GameController(std::unique_ptr<SnakeModel> model);
    ~GameController();
    void handleUserInput(UserAction_t action);
    GameInfo_t getGameInfo();
private:
    void updateModel();
    void copyField(int** dest);
    void allocateField(int*** field, int rows, int cols);
    void freeField(int*** field, int rows);
    std::unique_ptr<SnakeModel> model_;
    GameInfo_t game_info_;
};
} // namespace s21
#endif // SRC_BRICK_GAME_SNAKE_CONTROLLER_H_

