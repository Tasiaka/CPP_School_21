#ifndef TETRIS
#define TETRIS

#include <math.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#include "../common/common.h"

void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState(void);

void DRAWING_GAME(GameInfo_t data_tetris);

void USER_ACTION(int user_input);
void game_loop(void);

typedef enum {
  START = 0,
  SPAWN,
  MOVING,
  SHIFTING,
  ATTACHING,
  GAMEOVER,
  PAUSE,
  EXIT_STATE
} State;

typedef struct {
  int brick[4][4];
  int x;
  int y;
  char now;
  char future;
} Figure;

typedef struct {
  GameInfo_t data_tetris;
  Figure figure;
  UserAction_t input;
  int MotionField[20][10];
  int UsedField[20][10];
  bool NewInput;
  State state;
  unsigned long long Time;
  bool TimeStart;
  bool Allocation;
  bool BestScoreR;
  int score;
  int high_score;
  int level;
  int drop_interval;
} FullGameStat;

void RandomTetromin(FullGameStat *data_tetris_add);
void MainActFunc(FullGameStat *data_tetris_add);
void CalculateScore(FullGameStat *data_tetris_add);
void PushLeft(FullGameStat *data_tetris_add);
void PushRight(FullGameStat *data_tetris_add);
void GetReadyField(FullGameStat *data_tetris_add);
void Initialization(FullGameStat *data_tetris_add);
bool ControlGameOver(FullGameStat const *data_tetris_add);
void FutureFig(FullGameStat *data_tetris_add);
void CopyBrickToMoveField(FullGameStat *data_tetris_add);
bool ControlFalling(FullGameStat *data_tetris_add);
bool ControlBottomOfTetromino(FullGameStat const *data_tetris_add);
void Motion(FullGameStat *data_tetris_add);
void MotionBeforeTouch(FullGameStat *data_tetris_add);
void RemoveMemoryForField(int ***field, int rows);

FullGameStat *get_current_data_tetris_add();
void MainState(FullGameStat *data_tetris_add);

#endif
