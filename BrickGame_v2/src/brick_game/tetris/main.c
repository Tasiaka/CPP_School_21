#include "tetris.h"

int main(void) {
  initscr();  // в режим экраничка с текстом
  cbreak();  // для того чтобы с клавы сразу считывались знаки, без всяких enter
  halfdelay(2);          // задержка
  keypad(stdscr, TRUE);  // для считывания спец символовов(стрелочк напрмер)

  game_loop();

  endwin();
  return 0;
}
