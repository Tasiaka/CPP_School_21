#include "tetris.h"

static void FutureFigure(GameInfo_t *data_tetris, int next[][4]) {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) data_tetris->next[i][j] = next[i][j];
}

void RandomTetromin(FullGameStat *data_tetris_add)  // CHANGE
{
  int index = rand() % 7;
  if (index == 0) {
    int i[4][4] = {{0, 0, 0, 0}, {1, 1, 1, 1}, {0}, {0}};
    FutureFigure(&(data_tetris_add->data_tetris), i);
    data_tetris_add->figure.future = 'i';
  }
  if (index == 1) {
    int z[4][4] = {{1, 1, 0, 0}, {0, 1, 1, 0}, {0}, {0}};
    FutureFigure(&(data_tetris_add->data_tetris), z);
    data_tetris_add->figure.future = 'z';
  }
  if (index == 2) {
    int j[4][4] = {{1, 0, 0, 0}, {1, 1, 1, 0}, {0}, {0}};
    FutureFigure(&(data_tetris_add->data_tetris), j);
    data_tetris_add->figure.future = 'j';
  }
  if (index == 3) {
    int s[4][4] = {{0, 1, 1, 0}, {1, 1, 0, 0}, {0}, {0}};
    FutureFigure(&(data_tetris_add->data_tetris), s);
    data_tetris_add->figure.future = 's';
  }
  if (index == 4) {
    int t[4][4] = {{0, 1, 0, 0}, {1, 1, 1, 0}, {0}, {0}};
    FutureFigure(&(data_tetris_add->data_tetris), t);
    data_tetris_add->figure.future = 't';
  }
  if (index == 5) {
    int l[4][4] = {{0, 0, 1, 0}, {1, 1, 1, 0}, {0}, {0}};
    FutureFigure(&(data_tetris_add->data_tetris), l);
    data_tetris_add->figure.future = 'l';
  }
  if (index == 6) {
    int o[4][4] = {{0, 1, 1, 0}, {0, 1, 1, 0}, {0}, {0}};
    FutureFigure(&(data_tetris_add->data_tetris), o);
    data_tetris_add->figure.future = 'o';
  }
}