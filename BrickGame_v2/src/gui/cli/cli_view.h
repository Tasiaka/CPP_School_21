#ifndef SNAKE_VIEW
#define SNAKE_VIEW

#include "../../brick_game/common/common.h"

void DrawGame(const GameInfo_t& gi);
void ProcessInputFromNcurses(int ch);
void GameLoopCli();                  

#endif 