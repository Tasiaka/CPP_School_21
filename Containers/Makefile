OS = $(shell uname)

ifeq ("$(OS)","Linux")
	LEAKS_RUN_TEST = valgrind --tool=memcheck --leak-check=full --log-file="leaks.txt"
else
	LEAKS_RUN_TEST = leaks -atExit --
endif

CC=g++
CFLAGS=-std=c++17 -Wall -Wextra -Werror --coverage
LIBFLAGS=-lgtest --coverage -pthread 
OBJ_DIR=obj
SRC_DIR=src
TESTS_DIR=tests
CLANG_FORMAT = ../materials/linters/.clang-format

SRC_FILES=$(wildcard $(SRC_DIR)/*/*.cc)
OBJ_FILES=$(patsubst $(SRC_DIR)/%.cc, $(OBJ_DIR)/%.o, $(SRC_FILES))

TEST_MAIN = $(OBJ_DIR)/main_test.o
TEST_OBJ = $(OBJ_DIR)/test_array.o $(OBJ_DIR)/test_list.o $(OBJ_DIR)/test_tree.o $(OBJ_DIR)/test_vector.o $(OBJ_DIR)/test_queue.o $(OBJ_DIR)/test_stack.o
GCOV_OBJ = $(patsubst $(SRC_DIR)/%.cc, gcov_obj/%.o, $(SRC_FILES))

all: clean test

rebuild: clean all

gcc: $(OBJ_FILES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TESTS_DIR)/%.cc
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

test: libcontainers.a $(TEST_MAIN) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_MAIN) $(TEST_OBJ) libcontainers.a -o test $(LIBFLAGS)
	./test

test_m: clean
	$(CC) $(CFLAGS) tests/*.cc -o test $(LIBFLAGS)
	./test


libcontainers.a:
	g++ -Wall -Werror -Wextra -std=c++17 -c tests/*.cc
	ar -rcs libcontainers.a *.o
	rm -rf *.o
	ranlib libcontainers.a

clean:
	rm -rf $(OBJ_DIR) gcov_obj *.a test report
	rm -rf a.out *.gcno *.gcda *.o
	rm -rf *.info
	rm -rf leaks.txt

gcov_obj/%.o: $(SRC_DIR)/%.cc
	mkdir -p gcov_obj
	$(CC) $(CFLAGS) -c $< -o $@

gcov: $(GCOV_OBJ) $(TEST_MAIN) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(GCOV_FLAG) $(TEST_MAIN) $(TEST_OBJ) $(GCOV_OBJ) -o test $(LIBFLAGS)
	./test

gcovr_report: gcov
	mkdir -p report
	gcovr --html-details report/index.html --html-medium-threshold 80 --html-high-threshold 100 --html-title "(＾• ω •＾) Coverage report U・ᴥ・U " --exclude tests --exclude-directories tests --object-directory .

lcov: gcov
	./test
	lcov -t "test" -o test.info -c -d ./
	lcov --remove test.info '/usr/include/*' '/usr/local/include/*' '*/tests/*' -o test_filtered.info
	genhtml -o report test_filtered.info

clang:
	clang-format --style=file:$(CLANG_FORMAT) -i *.h ./*/*.tpp ./*/*.cc ./*/*.h
	clang-format --style=file:$(CLANG_FORMAT) -n *.h ./*/*.tpp ./*/*.cc ./*/*.h

leak_test: clean libcontainers.a test
	$(LEAKS_RUN_TEST) ./test

check:
	cppcheck -q --enable=warning,portability --inconclusive --suppress=missingIncludeSystem --suppress=*:tests/* .


.PHONY: all clean test libcontainers.a gcovr_report rebuild


# TARGET = s21_containers.a
# CC = gcc
# CFLAGS = -Wall -Werror -Wextra -std=c++17 -lstdc++
# TEST_FLAGS = -lgtest -pthread
# TEST_TARGET = testing_exe

# all: test

# clean:
# 	@rm -rf *.o *.a *.out *.log $(TEST_TARGET)


