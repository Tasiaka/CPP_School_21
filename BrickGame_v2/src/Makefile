CPP      = g++
CC       = gcc
AR       = ar
RANLIB   = ranlib

CFLAGS   = -Wall -Werror -Wextra
CPPFLAGS = $(CFLAGS) -std=c++17
TESTFLAGS = -lpthread
LDLIBS   = -fprofile-arcs -ftest-coverage


DIR_TET = brick_game/tetris
DIR_SN  = brick_game/snake
DIR_GUI     = gui/cli
DIR_BIN     = ./bin
DIR_BUILD := build

GTEST_INC = /opt/homebrew/opt/googletest/include
GTEST_LIB = /opt/homebrew/opt/googletest/lib

CHECK_INC = /opt/homebrew/opt/check/include
CHECK_LIB = /opt/homebrew/opt/check/lib

LIB_TETRIS = tetris.a
LIB_SNAKE  = snake.a


LLVM_COV = /opt/homebrew/opt/llvm/bin/llvm-cov


SOURCES_C_TET   = $(wildcard $(DIR_TET)/*.c)

SOURCES_CPP_SN  = $(wildcard $(DIR_SN)/*.cpp) $(wildcard $(DIR_SN)/*.cpp)

SOURCES_CPP_CLI = $(wildcard $(DIR_GUI)/*.cpp) $(wildcard $(DIR_GUI)/*.cpp)

SOURCES_TEST    = $(wildcard ./tests/*.cpp) $(wildcard ./tests/*.cpp)


OBJECTS_C_TET    = $(SOURCES_C_TET:.c=.o)
OBJECTS_CPP_SN   = $(patsubst %.cpp,%.o,$(filter %.cpp,$(SOURCES_CPP_SN))) \
                   $(patsubst %.cpp,%.o,$(filter %.cpp,$(SOURCES_CPP_SN)))
OBJECTS_CPP_CLI  = $(patsubst %.cpp,%.o,$(filter %.cpp,$(SOURCES_CPP_CLI))) \
                   $(patsubst %.cpp,%.o,$(filter %.cpp,$(SOURCES_CPP_CLI)))


.PHONY: all console desktop test gcov_report install uninstall dvi dist clean

all: desktop console

OBJS_CLI := gui/cli/cli_hub.o gui/cli/cli_main.o gui/cli/cli_view.o

console: $(OBJS_CLI) snake.a tetris.a
	mkdir -p ../build
	$(CXX) $(CXXFLAGS) -o ../build/BrickGame_cli $^ -lncurses
	rm -rf *.a

desktop:
	@mkdir -p ../build/desk
	cd ../build/desk && qmake6 ../../src/gui/desktop
	cd ../build/desk && make
	rm -rf ../build/desk/*.o 
	mv ../build/desk/BrickGame_desktop ../build/BrickGame_desktop


$(LIB_TETRIS): $(OBJECTS_C_TET)
	$(AR) rcs $@ $^
	$(RANLIB) $@

$(LIB_SNAKE): $(OBJECTS_CPP_SN)
	$(AR) rcs $@ $^
	$(RANLIB) $@


test: clean test_tetris test_snake
	rm -f *.a *.o test_tetris test_snake tests/*.o

test_tetris: $(LIB_TETRIS)
	$(CC)  $(CFLAGS) -I$(CHECK_INC) -c -o tests/test.o   tests/test.c
	$(CC)  $(CFLAGS) -I$(CHECK_INC) -c -o tests/testik.o tests/testik.c
	$(CPP) $(CFLAGS) tests/test.o tests/testik.o -o test_tetris tetris.a \
	  -L$(CHECK_LIB) -lcheck -lm -lpthread
	./test_tetris

test_snake: $(LIB_SNAKE)
	$(CPP) $(CPPFLAGS) -I$(GTEST_INC) -c -o tests/snake_gtest.o tests/snake_gtest.cpp
	$(CPP) $(CPPFLAGS) tests/snake_gtest.o -o test_snake snake.a \
	  -L$(GTEST_LIB) -lgtest -lgtest_main -lpthread
	./test_snake

GCOV_WRAPPER := .tools/gcov-llvm

gcov_report: clean
	make CFLAGS="$(CFLAGS) --coverage" CPPFLAGS="$(CPPFLAGS) --coverage" test_tetris
	make CFLAGS="$(CFLAGS) --coverage" CPPFLAGS="$(CPPFLAGS) --coverage" test_snake

	mkdir -p .tools
	@echo '#!/bin/sh' >  $(GCOV_WRAPPER)
	@echo 'exec "$(LLVM_COV)" gcov "$$@"' >> $(GCOV_WRAPPER)
	chmod +x $(GCOV_WRAPPER)

	rm -f coverage.info coverage.filtered.info
	lcov --gcov-tool "$(GCOV_WRAPPER)" --directory . --capture --output-file coverage.info --ignore-errors inconsistent,unsupported,format,unused
	lcov --remove coverage.info 'tests/*' '*.h' 'v1' -o coverage.filtered.info
	mkdir -p coverage_report
	genhtml coverage.filtered.info --output-directory coverage_report --ignore-errors category,unused
	@xdg-open coverage_report/index.html >/dev/null 2>&1 || open coverage_report/index.html >/dev/null 2>&1 || true

	rm -f *.a *.o test_tetris test_snake tests/*.o tests/*.gc* *.gc* brick_game/*/*.gc* brick_game/*/*.o coverage.*

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c -o $@ $<

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c -o $@ $<


install: clean console desktop
	@mkdir -p $(DIR_BIN)
	cp build_desk/desktop $(DIR_BIN)
	cp build_cli/console $(DIR_BIN)

uninstall:
	rm -rf $(DIR_BIN)

dvi:
	@true

dist:
	@mkdir -p $(PROJECT)-2.0
	cp -r brick_game gui Makefile $(PROJECT)-2.0
	tar -czf $(PROJECT)-2.0.tar.gz $(PROJECT)-2.0
	rm -rf $(PROJECT)-2.0

clean:
	rm -f $(DIR_TET)/*.o $(DIR_SN)/*.o $(DIR_GUI)/*.o ./tests/*.o
	rm -f $(LIB_TETRIS) $(LIB_SNAKE) test gcov_r
	rm -rf build_cli build_desk coverage_report ../build desk .tools coverage_report
	rm -f *.gcno *.gcda *.gcov test_* tests/*.o *.gc* brick_game/*/*.gc* tests/*.gc* coverage.* 

style:
	clang-format -i --style=Google brick_game/*/* gui/*/* tests/*

