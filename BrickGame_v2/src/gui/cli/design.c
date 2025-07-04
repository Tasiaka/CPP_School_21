#include <ncurses.h>
#include "../../brick_game/tetris/tetris.h" // Подключаем наш главный заголовочный файл с логикой

// Прототипы статических функций
static void SIDES(void);
static void GAME_PAGE_STAT(GameInfo_t data_tetris);
static void FIELD(GameInfo_t data_tetris);
static void GAME_OVER(void);
static void PAUS(void);
static void KEYS(void);

// Основная функция отрисовки
void DRAWING_GAME(GameInfo_t data_tetris) {
  clear();
  if (data_tetris.field != NULL) {
    GAME_PAGE_STAT(data_tetris);
    FIELD(data_tetris);
    KEYS();
    SIDES();
  }
  if (data_tetris.pause == 1) {
    PAUS();
    KEYS();
    SIDES();
  }
  if (data_tetris.pause == 2) {
    GAME_OVER();
  }
  refresh();
}

static void FIELD(GameInfo_t data_tetris) {
  for (int i = 0; i < 20; i++)
    for (int j = 0; j < 10; j++)
      if (data_tetris.field[i][j] == 1) {
        mvaddch(i + 1, j * 2 + 1, '[');
        mvaddch(i + 1, j * 2 + 2, ']');
      }
}

static void SIDES(void) {
  const char side = '|';
  int rows = 22, columns = 22;
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) {
      if (i == 0 || i == rows - 1) {
        mvaddch(i, j, side);
      }
      if (j == 0 || j == columns - 1) {
        mvaddch(i, j, side);
      }
    }
}

static void KEYS(void) {
  mvaddstr(1, 30, "s, S - START, RESTART");
  mvaddstr(2, 30, "t, T - EXIT");
  mvaddstr(3, 30, "a, A - ACTION");
  mvaddstr(4, 30, "p, P - PAUS, RESUME");
  mvaddstr(5, 30, "<- - LEFT");
  mvaddstr(6, 30, "-> - RIGHT");
  mvaddstr(7, 30, "down controller - FASTER");
}

static void GAME_OVER(void) {
  mvaddstr(10, 1, "XXXXXXXXXXXXXXXXXXXX");
  mvaddstr(11, 3, "G A M E  O V E R");
  mvaddstr(12, 1, "XXXXXXXXXXXXXXXXXXXX");
}

static void PAUS(void) {
  mvaddstr(10, 1, "XXXXXXXXXXXXXXXXXXXX");
  mvaddstr(11, 6, "P A U S E");
  mvaddstr(12, 1, "XXXXXXXXXXXXXXXXXXXX");
}

static void GAME_PAGE_STAT(GameInfo_t data_tetris) {
  mvaddstr(11, 30, "BEST SCORE");
  mvprintw(12, 32, "%d", data_tetris.high_score);

  mvaddstr(15, 30, "SCORE");
  mvprintw(16, 32, "%d", data_tetris.score);

  mvaddstr(18, 31, "NEXT");
  if (data_tetris.next) {
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
        if (data_tetris.next[i][j] == 1) {
          mvaddch(i + 19, j * 2 + 30, '[');
          mvaddch(i + 19, j * 2 + 31, ']');
        }
  }
}
