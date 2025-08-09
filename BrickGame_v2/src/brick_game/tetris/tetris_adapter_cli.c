#include "tetris.h"


void TetrisUserInput(UserAction_t user_input, bool hold) {
  (void)hold;
  FullGameStat *st = get_current_data_tetris_add();
  if (!st->NewInput) {
    st->input = user_input;
    st->NewInput = true;
  }
}

GameInfo_t TetrisUpdateCurrentState(void) {
  FullGameStat *st = get_current_data_tetris_add();
  MainState(st);
  return st->data_tetris;
}
