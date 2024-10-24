
all: clean s21_matrix_oop.a

s21_matrix_oop.a:
	g++ -Wall -Werror -Wextra -std=c++17 -c project/*.cc
	ar rc s21_matrix_oop.a *.o 
	rm -rf *.o
	ranlib s21_matrix_oop.a

test: clean
	g++ -Wall -Werror -Wextra -std=c++17 tests/*.cc project/*.cc -lgtest -lpthread -o testik
	./testik
	rm -rf testik

gcov_report: clean
	g++ --coverage project/*.cc tests/*.cc -o testik  -Wall -Werror -Wextra  -std=c++17 -lgtest -lpthread
	./testik
	lcov -c -d . -o coverage.info  --ignore-errors inconsistent 
	genhtml coverage.info --output-directory report  --ignore-errors inconsistent 
	open report/*/*/CPP1_s21_matrixplus*/src/project/index.html
	rm -f *.o *.gc* *.info testik

clean:
	rm -rf *.a *.o testik *.gc* *.info
	rm -rf report

style:
	clang-format -style=Google -i project/* tests/*

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem project/*.cc 

# leak: clean
# 	g++ -Wall -Werror -Wextra -std=c++17 tests/*.cc project/*.cc -lgtest -lpthread -o testik
# 	leaks -atExit -- ./testik
# 	make clean 
# 	g++ -Wall -Werror -Wextra -std=c++17 tests/*.cc project/*.cc -lgtest -lpthread -o testik
# 	leaks -atExit -- ./testik
# 	make clean 