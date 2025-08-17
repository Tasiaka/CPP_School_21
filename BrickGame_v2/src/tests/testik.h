#ifndef GAME_VIEW
#define GAME_VIEW
#include <check.h>

#define userInput TetrisUserInput
#define updateCurrentState TetrisUpdateCurrentState
#include "../brick_game/tetris/tetris.h"

#ifdef __cplusplus
extern "C" {
#endif
void TetrisUserInput(UserAction_t action, bool hold);
GameInfo_t TetrisUpdateCurrentState(void);
#ifdef __cplusplus
}
#endif

void run_tests(void);
void run_testcase(Suite *testcase);
Suite *game_test(void);
void RESTARTing(FullGameStat *data_tetris_add);

#endif