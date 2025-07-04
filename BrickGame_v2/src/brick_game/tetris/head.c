#include "tetris.h"
void userInput(UserAction_t user_input, bool hold) {
  (void)hold;
  FullGameStat *s = get_current_data_tetris_add();
  if (!s->NewInput) { s->input = user_input; s->NewInput = true; }
}
GameInfo_t updateCurrentState(void) {
  FullGameStat *s = get_current_data_tetris_add();
  MainState(s);
  return s->data_tetris;
}
void initGame() {
    FullGameStat *data = get_current_data_tetris_add();
    if (!data->Allocation) { Initialization(data); }
    data->state = START;
}
void destroyGame() {
    FullGameStat *data = get_current_data_tetris_add();
    RemoveMemoryForField(&data->data_tetris.field, 20);
    RemoveMemoryForField(&data->data_tetris.next, 4);
    data->Allocation = false;
}
