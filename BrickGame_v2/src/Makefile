PROJECT        := brickgame
ROOT_DIR       := ..
SRC_DIR        := .
BUILD_DIR      := $(ROOT_DIR)/build

BIN_PATH       := $(BUILD_DIR)/brickgame_cli

CXX            ?= c++
CC             ?= cc
AR             ?= ar
RANLIB         ?= ranlib


CXXFLAGS       ?= -std=c++17 -Wall -Wextra -Werror -pedantic -O2
CFLAGS         ?= -std=c11  -Wall -Wextra -Werror -O2
CPPFLAGS       ?= -I$(SRC_DIR)
LIBS           ?= -lncurses


SNAKE_DIR      := brick_game/snake
TETRIS_DIR     := brick_game/tetris
CLI_DIR        := gui/cli

LIB_SNAKE      := $(BUILD_DIR)/libbrickgame_snake.a
LIB_TETRIS     := $(BUILD_DIR)/libbrickgame_tetris.a

SNAKE_SRC := \
  $(SNAKE_DIR)/snake_model.cc \
  $(SNAKE_DIR)/snake_fsm.cc \
  $(SNAKE_DIR)/snake_controller.cc \
  $(SNAKE_DIR)/snake_adapter_c_api.cc

CLI_SRC := \
  $(CLI_DIR)/cli_view.cc \
  $(CLI_DIR)/cli_main.cc \
  $(CLI_DIR)/cli_hub.cc


TETRIS_SRC := \
  $(TETRIS_DIR)/addition.c \
  $(TETRIS_DIR)/controlling.c \
  $(TETRIS_DIR)/figure.c \
  $(TETRIS_DIR)/moving.c \
  $(TETRIS_DIR)/score.c \
  $(TETRIS_DIR)/tetris_adapter_cli.c


SNAKE_OBJ  := $(SNAKE_SRC:%.cc=$(BUILD_DIR)/%.o)
CLI_OBJ    := $(CLI_SRC:%.cc=$(BUILD_DIR)/%.o)
TETRIS_OBJ := $(TETRIS_SRC:%.c=$(BUILD_DIR)/%.o)


.PHONY: all clean install uninstall dist dvi tests run

all: $(BIN_PATH)

$(BUILD_DIR)/%.o: %.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(LIB_SNAKE): $(SNAKE_OBJ)
	@mkdir -p $(dir $@)
	$(AR) rcs $@ $^
	@$(RANLIB) $@ >/dev/null 2>&1 || true

ifeq ($(NO_TETRIS),1)
TETRIS_LIB_SWITCH :=
else
TETRIS_LIB_SWITCH := $(LIB_TETRIS)
endif

$(LIB_TETRIS): $(TETRIS_OBJ)
	@mkdir -p $(dir $@)
	$(AR) rcs $@ $^
	@$(RANLIB) $@ >/dev/null 2>&1 || true


$(BIN_PATH): $(LIB_SNAKE) $(TETRIS_LIB_SWITCH) $(CLI_OBJ)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CLI_OBJ) $(LIB_SNAKE) $(TETRIS_LIB_SWITCH) $(LIBS) -o $@
	@echo "Built: $@"

run: $(BIN_PATH)
	$(BIN_PATH)


PREFIX         ?= /usr/local
DESTDIR        ?=

install: all
	@mkdir -p $(DESTDIR)$(PREFIX)/bin
	@mkdir -p $(DESTDIR)$(PREFIX)/lib
	@cp -f $(BIN_PATH) $(DESTDIR)$(PREFIX)/bin/
	@cp -f $(LIB_SNAKE) $(DESTDIR)$(PREFIX)/lib/
ifneq ($(NO_TETRIS),1)
	@cp -f $(LIB_TETRIS) $(DESTDIR)$(PREFIX)/lib/
endif
	@echo "Installed to $(DESTDIR)$(PREFIX)"

uninstall:
	@rm -f $(DESTDIR)$(PREFIX)/bin/$(notdir $(BIN_PATH))
	@rm -f $(DESTDIR)$(PREFIX)/lib/$(notdir $(LIB_SNAKE))
ifneq ($(NO_TETRIS),1)
	@rm -f $(DESTDIR)$(PREFIX)/lib/$(notdir $(LIB_TETRIS))
endif
	@echo "Uninstalled."

dvi:
	@echo "Generate docs here (e.g., doxygen)."

dist:
	@tar czf $(PROJECT).tar.gz $(SRC_DIR) Makefile README.md || \
		tar czf $(PROJECT).tar.gz $(SRC_DIR) Makefile

tests:
	@echo "Place unit tests here (e.g., gtest)."

clean:
	@rm -rf $(BUILD_DIR) $(PROJECT).tar.gz
