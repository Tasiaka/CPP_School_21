#ifndef BRICK_GAME_COMMON_BRICK_GAME_H
#define BRICK_GAME_COMMON_BRICK_GAME_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// Константы «кнопок»
typedef enum {
    Start,
    Pause,
    Terminate,
    Left,
    Right,
    Up,
    Down,
    Action
} UserAction_t;

// Информация для отрисовки
typedef struct {
    int **field;      // игровое поле [20][10]
    int **next;       // «next» для Tetris (или NULL для Snake)
    int score;        // текущие очки
    int high_score;   // рекорд
    int level;        // уровень (Tetris)
    int speed;        // скорость (если нужна)
    int pause;        // флаг паузы/выхода
} GameInfo_t;

// C-API, реализованное в head.c (tetris) и в твоей snake-библиотеке
void initGame(void);
void destroyGame(void);
void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState(void);

#ifdef __cplusplus
}
#endif
#endif  // BRICK_GAME_COMMON_BRICK_GAME_H
