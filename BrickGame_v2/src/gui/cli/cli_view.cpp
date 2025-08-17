#include "cli_view.h"

#include <ncurses.h>

#include <chrono>
#include <cstring>

#include "cli_hub.h"

namespace {

unsigned long long NowMs() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(steady_clock::now().time_since_epoch())
      .count();
}

bool g_actionActive = false;
unsigned long long g_lastSpaceMs = 0;
constexpr int kActionReleaseMs = 250;

void DrawSides() {
  const char side = '|';
  const int rows = 22;
  const int cols = 22;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (i == 0 || i == rows - 1 || (j == 0 && i > 0) ||
          (j == cols - 1 && i > 0)) {
        mvaddch(i, j, side);
      }
    }
  }
}

void DrawBannerCentered(const char* text) {
  int len = static_cast<int>(std::strlen(text));
  int x = 1 + (20 - len) / 2;
  if (x < 1) x = 1;
  mvaddstr(10, 1, "XXXXXXXXXXXXXXXXXXXX");
  mvaddstr(11, x, text);
  mvaddstr(12, 1, "XXXXXXXXXXXXXXXXXXXX");
}

void DrawKeys(bool snake_active) {
  mvaddstr(1, 30, "s/S - START/RESTART");
  mvaddstr(2, 30, "t/T - EXIT (to menu)");
  if (snake_active) {
    mvaddstr(3, 30, "SPACE - ACTION (HOLD)");
    mvaddstr(4, 30, "p/P - PAUSE/RESUME");
    mvaddstr(5, 30, "<- / -> TURN LEFT/RIGHT");
  } else {
    mvaddstr(3, 30, "SPACE/UP - ROTATE");
    mvaddstr(4, 30, "p/P - PAUSE/RESUME");
    mvaddstr(5, 30, "<- / -> MOVE, DOWN - FAST DROP");
  }
}

static void DrawNextTetris(const GameInfo_t& gi) {
  mvaddstr(18, 31, "NEXT");
  if (!gi.next) return;
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 4; ++j)
      if (gi.next[i][j] == 1) {
        mvaddch(i + 19, j * 2 + 30, '[');
        mvaddch(i + 19, j * 2 + 31, ']');
      }
}

void DrawSidebar(const GameInfo_t& gi, const char* game_name,
                 bool snake_active) {
  mvaddstr(7, 30, "GAME");
  mvaddstr(8, 32, game_name);
  mvaddstr(11, 30, "BEST SCORE");
  mvprintw(12, 32, "%d", gi.high_score);
  mvaddstr(13, 30, "LEVEL");
  mvprintw(14, 32, "%d", gi.level);
  mvaddstr(15, 30, "SCORE");
  mvprintw(16, 32, "%d", gi.score);

  if (snake_active) {
    mvaddstr(18, 30, "SPEED (ms)");
    mvprintw(19, 32, "%d", gi.speed);
  } else {
    DrawNextTetris(gi);
  }
}

static void DrawFieldSnake(const GameInfo_t& gi) {
  if (!gi.field) return;
  for (int r = 0; r < 20; ++r)
    for (int c = 0; c < 10; ++c) {
      int v = gi.field[r][c];
      if (v == 1) {
        mvaddch(r + 1, c * 2 + 1, '[');
        mvaddch(r + 1, c * 2 + 2, ']');
      } else if (v == 2) {
        mvaddch(r + 1, c * 2 + 1, '(');
        mvaddch(r + 1, c * 2 + 2, ')');
      }
    }
}

static void DrawFieldTetris(const GameInfo_t& gi) {
  if (!gi.field) return;
  for (int r = 0; r < 20; ++r)
    for (int c = 0; c < 10; ++c)
      if (gi.field[r][c]) {
        mvaddch(r + 1, c * 2 + 1, '[');
        mvaddch(r + 1, c * 2 + 2, ']');
      }
}

void DrawField(const GameInfo_t& gi, bool snake_active) {
  if (snake_active) {
    DrawFieldSnake(gi);
  } else {
    DrawFieldTetris(gi);
  }
}

}  // namespace

void DrawGame(const GameInfo_t& gi) {
  clear();

  const bool snake_active = s21::IsSnakeActive();
  DrawSidebar(gi, s21::ActiveGameName(), snake_active);
  DrawField(gi, snake_active);
  DrawKeys(snake_active);
  DrawSides();

  if (gi.pause == 1) DrawBannerCentered("P A U S E");
  if (gi.pause == 2) DrawBannerCentered("G A M E  O V E R");

  if (snake_active && gi.level == 10 && gi.score >= 200) {
    DrawBannerCentered("Y O U   W I N");
  }

  refresh();
}

static void ProcessInputForActiveGame(int ch) {
  if (s21::IsSnakeActive()) {
    switch (ch) {
      case ' ': {
        g_lastSpaceMs = NowMs();
        if (!g_actionActive) {
          g_actionActive = true;
          s21::SendInputToActiveGame(Action, true);
        }
        break;
      }
      case 's':
      case 'S':
        s21::SendInputToActiveGame(Start, false);
        break;
      case 'p':
      case 'P':
        s21::SendInputToActiveGame(Pause, false);
        break;
      case 't':
      case 'T':
        s21::SendInputToActiveGame(Terminate, false);
        break;
      case KEY_LEFT:
        s21::SendInputToActiveGame(Left, false);
        break;
      case KEY_RIGHT:
        s21::SendInputToActiveGame(Right, false);
        break;
      default:
        break;
    }
  } else {
    switch (ch) {
      case ' ':
      case KEY_UP:
        s21::SendInputToActiveGame(Action, false);
        break;
      case 's':
      case 'S':
        s21::SendInputToActiveGame(Start, false);
        break;
      case 'p':
      case 'P':
        s21::SendInputToActiveGame(Pause, false);
        break;
      case 't':
      case 'T':
        s21::SendInputToActiveGame(Terminate, false);
        break;
      case KEY_LEFT:
        s21::SendInputToActiveGame(Left, false);
        break;
      case KEY_RIGHT:
        s21::SendInputToActiveGame(Right, false);
        break;
      case KEY_DOWN:
        s21::SendInputToActiveGame(Down, false);
        break;
      default:
        break;
    }
  }
}

void GameLoopCli() {
  g_actionActive = false;
  g_lastSpaceMs = 0;

  GameInfo_t gi{};
  while (gi.pause != 3) {
    gi = s21::UpdateActiveGameState();
    DrawGame(gi);

    int ch = getch();
    if (ch != ERR) ProcessInputForActiveGame(ch);

    if (s21::IsSnakeActive() && g_actionActive) {
      unsigned long long now = NowMs();
      if ((now - g_lastSpaceMs) > static_cast<unsigned>(kActionReleaseMs)) {
        g_actionActive = false;
        s21::SendInputToActiveGame(Action, false);
      }
    }
  }
}

void MainMenuLoop() {
  timeout(-1);

  while (true) {
    clear();
    mvaddstr(3, 6, "BRICK GAME");
    mvaddstr(6, 6, "[1] Snake");
    mvaddstr(7, 6, "[2] Tetris");
    mvaddstr(9, 6, "q - quit");
    refresh();

    int ch = getch();
    if (ch == '1') {
      s21::SelectGame(s21::GameKind::Snake);
      halfdelay(1);
      GameLoopCli();
      timeout(-1);
    } else if (ch == '2') {
      s21::SelectGame(s21::GameKind::Tetris);
      halfdelay(1);
      GameLoopCli();
      timeout(-1);
    } else if (ch == 'q' || ch == 'Q') {
      break;
    }
  }
}
