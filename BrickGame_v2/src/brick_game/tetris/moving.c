#include "tetris.h"

static bool ControlContactLeft(FullGameStat *data_tetris_add) {
  bool Result = false;
  if (data_tetris_add->figure.y == 0) {
    for (int i = 0; i < 4; i++)
      if (data_tetris_add->figure.brick[i][0] == 1) Result = true;
  }
  if (data_tetris_add->figure.y == -1) {
    for (int i = 0; i < 4; i++)
      if (data_tetris_add->figure.brick[i][1] == 1) Result = true;
  }
  for (int i = 0; i < 20; i++)
    for (int j = 1; j < 10; j++)
      if (data_tetris_add->MotionField[i][j] == 1 &&
          data_tetris_add->UsedField[i][j - 1] == 1)
        Result = true;
  return Result;
}

static bool ControlContactRight(FullGameStat *data_tetris_add) {
  bool Result = false;
  if (data_tetris_add->figure.y == 6) {
    for (int i = 0; i < 4; i++)
      if (data_tetris_add->figure.brick[i][3] == 1) Result = true;
  }
  if (data_tetris_add->figure.y == 7) {
    for (int i = 0; i < 4; i++)
      if (data_tetris_add->figure.brick[i][2] == 1) Result = true;
  }
  if (data_tetris_add->figure.y == 8) {
    for (int i = 0; i < 4; i++)
      if (data_tetris_add->figure.brick[i][1] == 1) Result = true;
  }
  for (int i = 0; i < 20; i++)
    for (int j = 0; j < 10 - 1; j++)
      if (data_tetris_add->MotionField[i][j] == 1 &&
          data_tetris_add->UsedField[i][j + 1] == 1)
        Result = true;
  return Result;
}

static bool ControlContactAfterAct(FullGameStat const *data_tetris_add) {
  bool Result = false;
  for (int i = 0; i < 20; i++)
    for (int j = 0; j < 10; j++) {
      if (data_tetris_add->MotionField[i][j] == 1 &&
          data_tetris_add->UsedField[i][j] == 1)
        Result = true;
    }
  return Result;
}

static void ControlYAfterAct(FullGameStat *data_tetris_add) {
  int y = data_tetris_add->figure.y;
  if (y == -1) {  // top left corner
    for (int i = 0; i < 4; i++)
      if (data_tetris_add->figure.brick[i][0] == 1) data_tetris_add->figure.y++;
  }
  if (y == 7) {
    for (int i = 0; i < 4; i++)
      if (data_tetris_add->figure.brick[i][3] == 1) data_tetris_add->figure.y--;
  }
  if (y == 8) {
    for (int i = 0; i < 4; i++)
      if (data_tetris_add->figure.brick[i][2] == 1) data_tetris_add->figure.y--;
  }
}

static bool ControlXAfterAct(FullGameStat *data_tetris_add) {
  bool Result = false;
  int x = data_tetris_add->figure.x;
  if (x == 17) {
    for (int j = 0; j < 4; j++)
      if (data_tetris_add->figure.brick[3][j] == 1) Result = true;
  }
  if (x == 18) {
    for (int j = 0; j < 4; j++)
      if (data_tetris_add->figure.brick[2][j] == 1) Result = true;
  }
  if (x == 19) {
    for (int j = 0; j < 4; j++)
      if (data_tetris_add->figure.brick[1][j] == 1) Result = true;
  }
  return Result;
}

static void CopyTetromino(Figure *what, Figure *where) {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) what->brick[i][j] = where->brick[i][j];
  what->x = where->x;
  what->y = where->y;
}

static void Rotation(Figure *figure) {
  int RotatFig[3][3] = {0};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) {
      int mas_j = j - 1;
      int mas_i = i - 1;
      int used_i = 0;
      int used_j = 0;
      used_i = mas_j;
      used_j = -mas_i;
      RotatFig[used_i + 1][used_j + 1] = figure->brick[i][j];
    }
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) figure->brick[i][j] = RotatFig[i][j];
}

static void RoationI(Figure *figure) {
  int RotatFig[4][4] = {0};
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) RotatFig[j][i] = figure->brick[i][j];
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) figure->brick[i][j] = RotatFig[i][j];
}

void MainActFunc(FullGameStat *data_tetris_add) {
  Figure terisik = {0};
  CopyTetromino(&terisik, &(data_tetris_add->figure));
  if (data_tetris_add->figure.now == 'o') {
    ;
  } else if (data_tetris_add->figure.now == 'i') {
    RoationI(&(data_tetris_add->figure));
  } else {
    Rotation(&(data_tetris_add->figure));
  }
  if (ControlXAfterAct(data_tetris_add)) {
    CopyTetromino(&(data_tetris_add->figure), &terisik);
  }
  ControlYAfterAct(data_tetris_add);
  CopyBrickToMoveField(data_tetris_add);
  if (ControlContactAfterAct(data_tetris_add)) {
    CopyTetromino(&(data_tetris_add->figure), &terisik);
    CopyBrickToMoveField(data_tetris_add);
  }
}

void PushRight(FullGameStat *data_tetris_add) {
  if (!ControlContactRight(data_tetris_add)) {
    data_tetris_add->figure.y++;
    CopyBrickToMoveField(data_tetris_add);
  }
}

void PushLeft(FullGameStat *data_tetris_add) {
  if (!ControlContactLeft(data_tetris_add)) {
    data_tetris_add->figure.y--;
    CopyBrickToMoveField(data_tetris_add);
  }
}