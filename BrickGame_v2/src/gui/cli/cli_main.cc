#include <ncurses.h>
#include "../../brick_game/common/common.h"
#include "cli_view.h"

int main() {
  initscr();
  cbreak();
  halfdelay(1);           // опрашиваем часто; тайминг в FSM
  keypad(stdscr, TRUE);
  noecho();

  GameLoopCli();

  endwin();
  return 0;
}
