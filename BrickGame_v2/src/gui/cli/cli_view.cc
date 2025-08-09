#include "cli_view.h"
#include <ncurses.h>

static void DrawField(const GameInfo_t& gi) {
  for (int r = 0; r < 20; ++r)
    for (int c = 0; c < 10; ++c) {
      if (gi.field[r][c] == 1) {        // змейка
        mvaddch(r + 1, c * 2 + 1, '[');
        mvaddch(r + 1, c * 2 + 2, ']');
      } else if (gi.field[r][c] == 2) { // яблоко
        mvaddch(r + 1, c * 2 + 1, '(');
        mvaddch(r + 1, c * 2 + 2, ')');
      }
    }
}

static void DrawSides() {
  const char side='|';
  int rows=22, cols=22;
  for (int i=0;i<rows;i++)
    for (int j=0;j<cols;j++) {
      if (i==0 || i==rows-1 || (j==0 && i>0) || (j==cols-1 && i>0)) mvaddch(i,j,side);
    }
}


static void DrawKeys() {
  mvaddstr(1, 30, "s, S - START, RESTART");
  mvaddstr(2, 30, "t, T - EXIT");
  mvaddstr(3, 30, "SPACE - ACTION (HOLD)");
  mvaddstr(4, 30, "p, P - PAUSE/RESUME");
  mvaddstr(5, 30, "<- / -> TURN LEFT/RIGHT");
}


static void DrawGameOver() {
  mvaddstr(10, 1, "XXXXXXXXXXXXXXXXXXXX");
  mvaddstr(11, 3, "G A M E  O V E R");
  mvaddstr(12, 1, "XXXXXXXXXXXXXXXXXXXX");
}
static void DrawPause() {
  mvaddstr(10, 1, "XXXXXXXXXXXXXXXXXXXX");
  mvaddstr(11, 6, "P A U S E");
  mvaddstr(12, 1, "XXXXXXXXXXXXXXXXXXXX");
}
static void DrawWin() {
  mvaddstr(10, 1, "XXXXXXXXXXXXXXXXXXXX");
  mvaddstr(11, 7, "Y O U  W I N");
  mvaddstr(12, 1, "XXXXXXXXXXXXXXXXXXXX");
}

static void DrawSidebar(const GameInfo_t& gi) {
  mvaddstr(11, 30, "BEST SCORE");
  mvprintw(12, 32, "%d", gi.high_score);
  mvaddstr(13, 30, "LEVEL");
  mvprintw(14, 32, "%d", gi.level);
  mvaddstr(15, 30, "SCORE");
  mvprintw(16, 32, "%d", gi.score);
  mvaddstr(18, 30, "SPEED (ms)");
  mvprintw(19, 32, "%d", gi.speed);
}

void DrawGame(const GameInfo_t& gi) {
  clear();
  if (gi.field) { DrawSidebar(gi); DrawField(gi); DrawKeys(); DrawSides(); }
  if (gi.pause == 1) { DrawPause(); DrawKeys(); DrawSides(); }
  if (gi.pause == 2) { DrawGameOver(); }
  if (gi.level == 10 && gi.score >= 200) { DrawWin(); }
  refresh();
}


#include <chrono>

static bool actionActive = false;
static unsigned long long lastAms = 0;
static const int ActionReleaseMs = 250; 

static unsigned long long NowMs() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}


void ProcessInputFromNcurses(int ch) {
  switch (ch) {
    case ' ': {
      lastAms = NowMs();
      if (!actionActive) {
        actionActive = true;
        userInput(Action, true);      
      }
      break;
    }
    case 's': case 'S': userInput(Start, false); break;
    case 'p': case 'P': userInput(Pause, false); break;
    case 't': case 'T': userInput(Terminate, false); break;
    case KEY_LEFT:  userInput(Left, false); break;
    case KEY_RIGHT: userInput(Right, false); break;
    default:
      break;
  }
}

void GameLoopCli() {
  GameInfo_t gi{};
  while (gi.pause != 3) {
    gi = updateCurrentState();
    DrawGame(gi);

    int ch = getch();              
    if (ch != ERR) ProcessInputFromNcurses(ch);

    unsigned long long now = NowMs();
    if (actionActive && (now - lastAms) > (unsigned)ActionReleaseMs) {
      actionActive = false;
      userInput(Action, false);    
    }
  }
}
