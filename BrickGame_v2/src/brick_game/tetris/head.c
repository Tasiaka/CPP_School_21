#include "tetris.h"

void userInput(UserAction_t user_input, bool hold) {
  (void)hold;
  FullGameStat *data_tetris_add = get_current_data_tetris_add();
  if (!data_tetris_add->NewInput) {
    data_tetris_add->input = user_input;
    data_tetris_add->NewInput = true;
  }
}

GameInfo_t updateCurrentState(void) {
  FullGameStat *data_tetris_add = get_current_data_tetris_add();
  MainState(data_tetris_add);

  return data_tetris_add->data_tetris;
}

void game_loop(void) {
  GameInfo_t data_tetris = {0};
  while (data_tetris.pause != 3) {
    data_tetris = updateCurrentState();
    DRAWING_GAME(data_tetris);
    USER_ACTION(getch());
  }
}

void USER_ACTION(int user_input) {
  switch (user_input) {
    case 'a':
      userInput(Action, false);
      break;
    case 's':
      userInput(Start, false);
      break;
    case 'p':
      userInput(Pause, false);
      break;
    case 't':
      userInput(Terminate, false);
      break;
    case 'A':
      userInput(Action, false);
      break;
    case 'S':
      userInput(Start, false);
      break;
    case 'P':
      userInput(Pause, false);
      break;
    case 'T':
      userInput(Terminate, false);
      break;
    case KEY_LEFT:
      userInput(Left, false);
      break;
    case KEY_RIGHT:
      userInput(Right, false);
      break;
    case KEY_UP:
      userInput(Up, false);
      break;
    case KEY_DOWN:
      userInput(Down, false);
      break;
    default:
      break;
  }
}
