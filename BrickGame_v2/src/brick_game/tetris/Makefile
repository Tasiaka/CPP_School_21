GCC = gcc 
CFLAGS = -Wall -Werror -Wextra -std=c11  

IMPORTANT = -lncurses
OBJECT_GCOV = addition.o controlling.o figure.o head.o moving.o score.o test.o testik.o
CHECK = -lcheck

ifeq ($(shell uname), Linux)
	CFLAGS +=lsubunit -lm
	CHECK = -lcheck_pic
endif

all: clean uninstall install

install:tetris_lib.a
	$(GCC) $(CFLAGS) -o GAME *.c ../../gui/cli/*.c tetris_lib.a $(IMPORTANT)
	make clean

clean: 
	rm -f *.o *.a *.gcno *.gcda BestScore test *.gcov *.info
# rm -rf report

tetris_lib.a:	
	$(GCC) $(CFLAGS) -c *.c ../../gui/cli/*.c 
	ar rc tetris_lib.a *.o
	ranlib tetris_lib.a

uninstall:
	rm -rf GAME

dvi:
	open readme.md
 	
dist:
	zip -r tetris.install.zip ./*


# make clean

gcov_report: clean test
	$(GCC) --coverage brick_game/tetris/*.c gui/cli/*.c testik/*.c -o test $(CHECK) $(IMPORTANT)
	lcov -t "testik" -o tetris.info -c -d .
	genhtml -o ./report tetris.info --exclude test.c
	open ./report/index.html
	make clean

cppchecker:
	cppcheck --enable=all --suppress=missingIncludeSystem  *.c ../../gui/cli/*.c 

style:
	clang-format -i --style=Google *.c ../../gui/cli/*.c *.h

