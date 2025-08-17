#include "tetris.h"

static void FullFieldZero(int **field, int rows, int columns);
static void MemoryForField(int ***field, int rows, int columns);
static unsigned long long NowTime();

static void BestScore(FullGameStat *data_tetris_add) {
  FILE *file = NULL;
  int high_score = 0;
  file = fopen("BestScore_Tetris", "r");
  if (file) {
    fscanf(file, "%d", &high_score);
    data_tetris_add->data_tetris.high_score = high_score;
    fclose(file);
  }
}

void GetReadyField(FullGameStat *data_tetris_add) {
  if (data_tetris_add->data_tetris.field != NULL) {
    for (int i = 0; i < 20; i++)
      for (int j = 0; j < 10; j++)
        if (data_tetris_add->MotionField[i][j] == 1 ||
            data_tetris_add->UsedField[i][j] == 1)
          data_tetris_add->data_tetris.field[i][j] = 1;
        else
          data_tetris_add->data_tetris.field[i][j] = 0;
  }
}

void Initialization(FullGameStat *data_tetris_add) {
  if (!data_tetris_add->Allocation) {
    MemoryForField(&(data_tetris_add->data_tetris.field), 20, 10);
    MemoryForField(&(data_tetris_add->data_tetris.next), 4, 4);
    data_tetris_add->Allocation = true;
  }
  data_tetris_add->data_tetris.level = 1;
  BestScore(data_tetris_add);
}

bool ControlGameOver(FullGameStat const *data_tetris_add) {
  bool Result = false;
  for (int j = 0; j < 10; j++)
    if (data_tetris_add->UsedField[0][j] == 1) Result = true;
  return Result;
}

void FutureFig(FullGameStat *data_tetris_add) {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      data_tetris_add->figure.brick[i][j] =
          data_tetris_add->data_tetris.next[i][j];
  data_tetris_add->figure.x = 0;  // height
  data_tetris_add->figure.y = 4;
  data_tetris_add->figure.now = data_tetris_add->figure.future;
  data_tetris_add->figure.future = 0;
}

void CopyBrickToMoveField(FullGameStat *data_tetris_add) {
  int x = data_tetris_add->figure.x;
  int y = data_tetris_add->figure.y;
  for (int i = 0; i < 20; i++)
    for (int j = 0; j < 10; j++) data_tetris_add->MotionField[i][j] = 0;
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      if (data_tetris_add->figure.brick[i][j] == 1)
        data_tetris_add->MotionField[i + x][j + y] = 1;
}

bool ControlFalling(FullGameStat *data_tetris_add) {
  bool Result = false;
  if (!data_tetris_add->TimeStart) {
    data_tetris_add->Time = NowTime();
    data_tetris_add->TimeStart = true;
  }
  long long unsigned int LevelSpeed =
      1000 / (data_tetris_add->data_tetris.level * 2);
  if (NowTime() - data_tetris_add->Time >= LevelSpeed &&
      data_tetris_add->state != EXIT_STATE &&
      data_tetris_add->data_tetris.pause != 1) {
    data_tetris_add->TimeStart = false;
    data_tetris_add->Time = 0;
    Result = true;
  }
  return Result;
}

bool ControlBottomOfTetromino(FullGameStat const *data_tetris_add) {
  bool Result = false;
  bool flag = false;
  for (int j = 0; j < 10; j++)
    if (data_tetris_add->MotionField[19][j] == 1) flag = true;

  bool Resultik = false;
  for (int i = 0; i < 20; i++)
    for (int j = 0; j < 10; j++)
      if (data_tetris_add->MotionField[i][j] == 1 &&
          data_tetris_add->UsedField[i + 1][j] == 1)
        Resultik = true;

  if (Resultik || flag) {
    Result = true;
  }
  return Result;
}

void Motion(FullGameStat *data_tetris_add) {
  data_tetris_add->figure.x++;
  CopyBrickToMoveField(data_tetris_add);
}

void MotionBeforeTouch(FullGameStat *data_tetris_add) {
  for (int i = 0; i < 20; i++)
    for (int j = 0; j < 10; j++)
      if (data_tetris_add->MotionField[i][j] == 1) {
        data_tetris_add->UsedField[i][j] = 1;
        data_tetris_add->MotionField[i][j] = 0;
      }
}

void RemoveMemoryForField(int ***field, int rows) {
  if (*field != NULL) {
    for (int row = 0; row < rows; row++) {
      if ((*field)[row] != NULL) free((*field)[row]);
    }
    free(*field);
  }
  *field = NULL;
}

static unsigned long long NowTime() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (unsigned long long)(tv.tv_sec) * 1000 +
         (unsigned long long)(tv.tv_usec) / 1000;
}

static void FullFieldZero(int **field, int rows, int columns) {
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) field[i][j] = 0;
}

static void MemoryForField(int ***field, int rows, int columns) {
  *field = (int **)malloc(20 * sizeof(int *));
  if (*field != NULL) {
    for (int row = 0; row < rows; row++)
      (*field)[row] = (int *)malloc(columns * sizeof(int));
    FullFieldZero(*field, rows, columns);
  }
}
