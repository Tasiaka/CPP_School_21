# Makefile для библиотек и консольного приложения
CC = gcc
CXX = g++
CFLAGS = -std=c11 -Wall -Wextra -Werror -g -fPIC
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -g -fPIC
LDFLAGS_CLI = -lncurses -ldl

BUILD_DIR = ../build
COMMON_API_DIR = brick_game/common

# --- Тетрис ---
TETRIS_DIR = brick_game/tetris
TETRIS_SRC = $(wildcard $(TETRIS_DIR)/*.c)
TETRIS_OBJ = $(patsubst %.c, $(BUILD_DIR)/%.o, $(TETRIS_SRC))
TETRIS_LIB = $(BUILD_DIR)/libtetris_lib.so

# --- Змейка ---
SNAKE_DIR = brick_game/snake
SNAKE_SRC = $(wildcard $(SNAKE_DIR)/*.cpp)
SNAKE_OBJ = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SNAKE_SRC))
SNAKE_LIB = $(BUILD_DIR)/libsnake_lib.so

# --- Консоль ---
CLI_DIR = gui/cli
CLI_SRC = $(wildcard $(CLI_DIR)/*.c)
CLI_OBJ = $(patsubst %.c, $(BUILD_DIR)/%.o, $(CLI_SRC))
CLI_APP = $(BUILD_DIR)/cli_app

# --- Цели ---
all: $(TETRIS_LIB) $(SNAKE_LIB) $(CLI_APP)

# Правила сборки библиотек
$(TETRIS_LIB): $(TETRIS_OBJ)
	$(CC) -shared -o $@ $^
$(SNAKE_LIB): $(SNAKE_OBJ)
	$(CXX) -shared -o $@ $^

# Правило сборки консольного приложения
$(CLI_APP): $(CLI_OBJ)
	$(CC) -o $@ $^ $(LDFLAGS_CLI)

# Правила для объектных файлов
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(COMMON_API_DIR) -c $< -o $@
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -I$(COMMON_API_DIR) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
