#ifndef CLI
#define CLI

#include "../../brick_game/common/common.h"

namespace s21 {

enum class GameKind { Snake, Tetris };

void SelectGame(GameKind kind);
void SendInputToActiveGame(UserAction_t action, bool hold);
GameInfo_t UpdateActiveGameState();
const char* ActiveGameName();
bool IsSnakeActive();

}  // namespace s21

#endif