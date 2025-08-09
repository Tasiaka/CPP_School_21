# ===== Project =====
PROJECT        := brickgame
PREFIX         ?= /usr/local
DESTDIR        ?=
SRC_DIR        := src
BUILD_DIR      := build
BIN_DIR        := bin

# ===== Toolchain =====
CXX            ?= c++
CC             ?= cc
AR             ?= ar
RANLIB         ?= ranlib

# ===== Flags =====
CXXFLAGS       ?= -std=c++17 -Wall -Wextra -Werror -pedantic -O2
CFLAGS         ?= -std=c11  -Wall -Wextra -Werror -O2
CPPFLAGS       ?= -I$(SRC_DIR)
LIBS           ?= -lncurses

# ===== Paths =====
SNAKE_DIR      := $(SRC_DIR)/brick_game/snake
TETRIS_DIR     := $(SRC_DIR)/brick_game/tetris
CLI_DIR        := $(SRC_DIR)/gui/cli

# ===== Targets =====
LIB_SNAKE      := $(BUILD_DIR)/libbrickgame_snake.a
LIB_TETRIS     := $(BUILD_DIR)/libbrickgame_tetris.a
CLI_BIN        := $(BIN_DIR)/brickgame_cli

# ===== Sources =====
SNAKE_SRC := \
  $(SNAKE_DIR)/snake_model.cc \
  $(SNAKE_DIR)/snake_fsm.cc \
  $(SNAKE_DIR)/snake_controller.cc \
  $(SNAKE_DIR)/snake_adapter_c_api.cc

CLI_SRC := \
  $(CLI_DIR)/cli_view.cc \
  $(CLI_DIR)/cli_main.cc \
  $(CLI_DIR)/cli_hub.cc

# Важно: из v1 тетриса НЕ тянем старые CLI/MAIN (design.c, main.c)
TETRIS_SRC := \
  $(TETRIS_DIR)/addition.c \
  $(TETRIS_DIR)/controlling.c \
  $(TETRIS_DIR)/figure.c \
  $(TETRIS_DIR)/tetris_adapter_cli.c\
  $(TETRIS_DIR)/moving.c \
  $(TETRIS_DIR)/score.c

# ===== Objects =====
SNAKE_OBJ   := $(SNAKE_SRC:%.cc=$(BUILD_DIR)/%.o)
CLI_OBJ     := $(CLI_SRC:%.cc=$(BUILD_DIR)/%.o)
TETRIS_OBJ  := $(TETRIS_SRC:%.c=$(BUILD_DIR)/%.o)

# ===== Phony =====
.PHONY: all clean install uninstall dist dvi tests run

# ===== Default =====
all: $(CLI_BIN)

# ===== Build rules =====
$(BUILD_DIR)/%.o: %.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

# Переименовываем userInput/updateCurrentState тетриса в TetrisUserInput/TetrisUpdateCurrentState
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) \
		-DuserInput=TetrisUserInput \
		-DupdateCurrentState=TetrisUpdateCurrentState \
		-c $< -o $@

$(LIB_SNAKE): $(SNAKE_OBJ)
	@mkdir -p $(dir $@)
	$(AR) rcs $@ $^
	$(RANLIB) $@ >/dev/null 2>&1 || true

# Позволяем выключить сборку тетриса флагом NO_TETRIS=1
ifeq ($(NO_TETRIS),1)
TETRIS_SWITCH :=
else
TETRIS_SWITCH := $(LIB_TETRIS)
endif

$(LIB_TETRIS): $(TETRIS_OBJ)
	@mkdir -p $(dir $@)
	$(AR) rcs $@ $^
	$(RANLIB) $@ >/dev/null 2>&1 || true

$(CLI_BIN): $(LIB_SNAKE) $(TETRIS_SWITCH) $(CLI_OBJ)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CLI_OBJ) $(LIB_SNAKE) $(TETRIS_SWITCH) $(LIBS) -o $@

# ===== Convenience =====
run: $(CLI_BIN)
	./$(CLI_BIN)

# ===== Install / Uninstall =====
install: all
	@mkdir -p $(DESTDIR)$(PREFIX)/bin
	@mkdir -p $(DESTDIR)$(PREFIX)/lib
	@cp -f $(CLI_BIN) $(DESTDIR)$(PREFIX)/bin/
	@cp -f $(LIB_SNAKE) $(DESTDIR)$(PREFIX)/lib/
ifneq ($(NO_TETRIS),1)
	@cp -f $(LIB_TETRIS) $(DESTDIR)$(PREFIX)/lib/
endif
	@echo "Installed to $(DESTDIR)$(PREFIX)"

uninstall:
	@rm -f $(DESTDIR)$(PREFIX)/bin/$(notdir $(CLI_BIN))
	@rm -f $(DESTDIR)$(PREFIX)/lib/$(notdir $(LIB_SNAKE))
ifneq ($(NO_TETRIS),1)
	@rm -f $(DESTDIR)$(PREFIX)/lib/$(notdir $(LIB_TETRIS))
endif
	@echo "Uninstalled."

# ===== Docs / Dist / Tests =====
dvi:
	@echo "Generate docs here (e.g., doxygen)."

dist:
	@tar czf $(PROJECT).tar.gz $(SRC_DIR) Makefile README.md || \
		tar czf $(PROJECT).tar.gz $(SRC_DIR) Makefile

tests:
	@echo "Place unit tests here (e.g., gtest)."

# ===== Clean =====
clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR) $(PROJECT).tar.gz
