#define _DEFAULT_SOURCE
#include "../../brick_game/common/brick_game.h"
#include "design.h"
#include <ncurses.h>
#include <dlfcn.h>   // Для динамической загрузки
#include <unistd.h>
#include <stdio.h>

// Указатели на функции из библиотеки
void (*lib_initGame)();
void (*lib_destroyGame)();
void (*lib_userInput)(UserAction_t, bool);
GameInfo_t (*lib_updateCurrentState)();

// Улучшенная функция загрузки с выводом ошибок
int load_library(const char* path) {
    void* handle = dlopen(path, RTLD_LAZY);
    if (!handle) {
        // Если не удалось загрузить, печатаем ошибку!
        fprintf(stderr, "Error loading library: %s\n", dlerror());
        return 0;
    }

    // Загружаем адреса функций
    lib_initGame = dlsym(handle, "initGame");
    lib_destroyGame = dlsym(handle, "destroyGame");
    lib_userInput = dlsym(handle, "userInput");
    lib_updateCurrentState = dlsym(handle, "updateCurrentState");

    // Проверяем, что все функции нашлись
    if (!lib_initGame || !lib_destroyGame || !lib_userInput || !lib_updateCurrentState) {
        fprintf(stderr, "Error resolving symbols in library: %s\n", dlerror());
        dlclose(handle);
        return 0;
    }
    return 1;
}

// Главный игровой цикл
void game_loop() {
    GameInfo_t info = {0};
    int key;
    while (1) { // Бесконечный цикл, выход по флагу
        if ((key = getch()) != ERR) {
            UserAction_t action; bool known = true;
            switch (key) {
                case 'a': case 'A': action = Action; break;
                case 's': case 'S': action = Start; break;
                case 'p': case 'P': action = Pause; break;
                case 't': case 'T': action = Terminate; break;
                case KEY_LEFT:      action = Left; break;
                case KEY_RIGHT:     action = Right; break;
                case KEY_UP:        action = Up; break;
                case KEY_DOWN:      action = Down; break;
                default: known = false; break;
            }
            if(known) lib_userInput(action, false);
        }
        
        info = lib_updateCurrentState();
        
        // Проверка на сигнал выхода из игры
        if(info.pause == 3) break;

        DRAWING_GAME(info);
        refresh();
        usleep(100000); // Задержка 100ms
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        // Улучшенное сообщение об использовании
        printf("BrickGame Console UI\n");
        printf("Usage: %s <path_to_library.so>\n", argv[0]);
        printf("Example: %s ../build/libtetris_lib.so\n", argv[0]);
        return 1;
    }

    // Запускаем из папки build, поэтому путь к библиотеке будет другим
    if (!load_library(argv[1])) {
        // Ошибка уже выведена в load_library
        return 1;
    }
    
    initscr(); cbreak(); noecho(); keypad(stdscr, TRUE); nodelay(stdscr, TRUE); curs_set(0);
    
    lib_initGame();
    game_loop();
    lib_destroyGame();
    
    endwin();
    
    return 0;
}
