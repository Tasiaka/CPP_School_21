/* --- Файл: tetris.h (внутренний заголовок) --- */
#ifndef SRC_BRICK_GAME_TETRIS_TETRIS_H_
#define SRC_BRICK_GAME_TETRIS_TETRIS_H_

#include "../common/brick_game.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef enum {
  START = 0, SPAWN, MOVING, SHIFTING, ATTACHING, GAMEOVER, PAUSE, EXIT_STATE
} State;
typedef struct {
  int brick[4][4]; int x; int y; char now; char future;
} Figure;
typedef struct {
  GameInfo_t data_tetris; Figure figure; UserAction_t input;
  int MotionField[20][10]; int UsedField[20][10];
  bool NewInput; State state; unsigned long long Time;
  bool TimeStart; bool Allocation;
} FullGameStat;

void MainState(FullGameStat *s);
FullGameStat *get_current_data_tetris_add();
void RandomTetromin(FullGameStat *s);
void MainActFunc(FullGameStat *s);
void CalculateScore(FullGameStat *s);
void PushLeft(FullGameStat *s);
void PushRight(FullGameStat *s);
void GetReadyField(FullGameStat *s);
void Initialization(FullGameStat *s);
bool ControlGameOver(const FullGameStat *s);
void FutureFig(FullGameStat *s);
void CopyBrickToMoveField(FullGameStat *s);
bool ControlFalling(FullGameStat *s);
bool ControlBottomOfTetromino(const FullGameStat *s);
void Motion(FullGameStat *s);
void MotionBeforeTouch(FullGameStat *s);
void RemoveMemoryForField(int ***field, int rows);

#endif