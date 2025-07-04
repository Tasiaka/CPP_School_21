#ifndef SRC_BRICK_GAME_COMMON_BRICK_GAME_API_H_
#define SRC_BRICK_GAME_COMMON_BRICK_GAME_API_H_

#include <stdbool.h>

typedef enum {
  Start, Pause, Terminate, Left, Right, Up, Down, Action
} UserAction_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

#ifdef __cplusplus
extern "C" {
#endif

void initGame();
void destroyGame();
void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();

#ifdef __cplusplus
}
#endif

#endif  // SRC_BRICK_GAME_COMMON_BRICK_GAME_API_H_
