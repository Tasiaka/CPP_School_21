#include <ncurses.h>

#include "cli_view.h"

int main() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  halfdelay(1);

  MainMenuLoop();

  endwin();
  return 0;
}
