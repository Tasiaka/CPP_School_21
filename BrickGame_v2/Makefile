PROJECT=brickgame
CXX?=g++
CXXFLAGS=-std=c++17 -Wall -Wextra -Werror -pedantic -O2
LDFLAGS=-lncurses

SRC_DIR=src
BG_DIR=$(SRC_DIR)/brick_game
SNAKE_DIR=$(BG_DIR)/snake
CLI_DIR=$(SRC_DIR)/gui/cli
BUILD_DIR=build
BIN_DIR=bin
PREFIX?=/usr/local

LIB=$(BUILD_DIR)/libbrickgame_snake.a
CLI=$(BIN_DIR)/brickgame_cli

SNAKE_SRC=$(SNAKE_DIR)/snake_model.cc $(SNAKE_DIR)/snake_fsm.cc $(SNAKE_DIR)/snake_controller.cc $(SNAKE_DIR)/snake_adapter_c_api.cc
CLI_SRC=$(CLI_DIR)/cli_view.cc $(CLI_DIR)/cli_main.cc
SNAKE_OBJ=$(SNAKE_SRC:%.cc=$(BUILD_DIR)/%.o)
CLI_OBJ=$(CLI_SRC:%.cc=$(BUILD_DIR)/%.o)

all: $(CLI)

$(BUILD_DIR)/%.o: %.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -c $< -o $@

$(LIB): $(SNAKE_OBJ)
	@mkdir -p $(dir $@)
	ar rcs $@ $^

$(CLI): $(LIB) $(CLI_OBJ)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CLI_OBJ) $(LIB) $(LDFLAGS) -o $@

install: all
	@mkdir -p $(DESTDIR)$(PREFIX)/bin
	@mkdir -p $(DESTDIR)$(PREFIX)/lib
	@cp -f $(CLI) $(DESTDIR)$(PREFIX)/bin/
	@cp -f $(LIB) $(DESTDIR)$(PREFIX)/lib/

uninstall:
	@rm -f $(DESTDIR)$(PREFIX)/bin/brickgame_cli
	@rm -f $(DESTDIR)$(PREFIX)/lib/libbrickgame_snake.a

clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR) dist.tar.gz

dist:
	@tar czf dist.tar.gz src Makefile README.md

dvi:
	@echo "Generate docs here (e.g., doxygen)"; true

tests:
	@echo "Place unit tests here (e.g., gtest)"; true
