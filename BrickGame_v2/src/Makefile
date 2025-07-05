# Компиляторы
CXX := g++
CC  := gcc

# Определяем ОС
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
  QT_PATH    := /opt/homebrew/opt/qt
  GTEST_INC  := /opt/homebrew/include
  GTEST_LIB  := /opt/homebrew/lib
  QT_CXXFLAGS  := -I$(QT_PATH)/include \
                   -I$(QT_PATH)/include/QtWidgets \
                   -I$(QT_PATH)/include/QtGui \
                   -I$(QT_PATH)/include/QtCore
  QT_LDFLAGS   := -F$(QT_PATH)/lib \
                   -framework QtWidgets \
                   -framework QtGui \
                   -framework QtCore
  TEST_FLAGS   := -I$(GTEST_INC) -L$(GTEST_LIB) -lgtest -lgtest_main -pthread
else
  QT_CXXFLAGS  := -I/usr/include/qt \
                   -I/usr/include/qt/QtWidgets \
                   -I/usr/include/qt/QtGui \
                   -I/usr/include/qt/QtCore
  QT_LDFLAGS   := -lQt5Widgets -lQt5Gui -lQt5Core
  TEST_FLAGS   := -lgtest -lgtest_main -pthread
endif

# Общие флаги
CFLAGS   := -std=c11 -Wall -Wextra -Werror -fPIC
CXXFLAGS := -std=c++17 -Wall -Wextra -Werror -fPIC $(QT_CXXFLAGS)

# Директории и файлы
SRC_DIR    := .
BUILD_DIR  := build
TEST_DIR   := tests
BIN_PREFIX := $(BUILD_DIR)/brickgame

# Источники
SNAKE_SRC  := $(wildcard brick_game/snake/*.cpp)
TETRIS_SRC := $(wildcard brick_game/tetris/*.c)
GUI_SRC   := gui/desktop/main_window.cpp \
             gui/desktop/tetris_widget.cpp \
             gui/desktop/snake_widget.cpp
CLI_SRC    := gui/cli/main.c
MAIN_SRC   := main.cpp
TEST_SRC   := $(wildcard $(TEST_DIR)/*.cpp)

# Объекты
SNAKE_OBJ  := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SNAKE_SRC))
TETRIS_OBJ := $(patsubst %.c,$(BUILD_DIR)/%.o,$(TETRIS_SRC))
GUI_OBJ    := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(GUI_SRC))
CLI_OBJ    := $(BUILD_DIR)/cli_main.o
MAIN_OBJ   := $(BUILD_DIR)/main.o
TEST_OBJ   := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(TEST_SRC))

# Цели по умолчанию
.PHONY: all gui cli tests install uninstall clean dist

all: gui cli

# GUI-приложение (Qt)
gui: $(BIN_PREFIX)_gui

$(BIN_PREFIX)_gui: $(MAIN_OBJ) $(SNAKE_OBJ) $(TETRIS_OBJ) $(GUI_OBJ)
	@mkdir -p $(dir $@)
	$(CXX) $^ -o $@ $(QT_LDFLAGS)

# CLI-приложение (ncurses + dlopen для Tetris/Snake)
cli: $(BIN_PREFIX)_cli

$(BIN_PREFIX)_cli: $(SNAKE_OBJ) $(TETRIS_OBJ) $(CLI_OBJ)
	@mkdir -p $(dir $@)
	$(CXX) $^ -o $@ -lncurses -ldl

# Сборка объектов из .cpp
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Сборка объектов из .c
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Главный объект
$(MAIN_OBJ): $(MAIN_SRC)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# CLI-объект
$(CLI_OBJ): $(CLI_SRC)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Тесты (только для Snake / GTest)
tests: $(SNAKE_OBJ) $(TEST_OBJ)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $^ -o $(BUILD_DIR)/tests $(TEST_FLAGS)
	$(BUILD_DIR)/tests

install:
	mkdir -p /usr/local/bin/brickgame
	cp $(BIN_PREFIX)_gui /usr/local/bin/brickgame/gui
	cp $(BIN_PREFIX)_cli /usr/local/bin/brickgame/cli

uninstall:
	rm -rf /usr/local/bin/brickgame

clean:
	rm -rf $(BUILD_DIR)

dist:
	tar czf brickgame_v2.tar.gz \
      src/brick_game src/gui src/tests src/main.cpp src/Makefile
