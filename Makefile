CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -I.
LDFLAGS = -lcheck -lm -lpthread 

OS := $(shell uname -s)

ifeq ($(OS),Darwin)
	ifneq ($(wildcard /opt/homebrew/include/*),)
		CFLAGS += -I/opt/homebrew/include
		LDFLAGS += -L/opt/homebrew/lib
	else
		CFLAGS += -I/usr/local/include
		LDFLAGS += -L/usr/local/lib
	endif
else ifeq ($(OS),Linux)
	LDFLAGS += -lsubunit -lrt
endif

LIB = s21_matrix.a

.PHONY: all clean test gcov_report style clang rebuild

LIB_SRC = $(wildcard functions/*.c)
OBJ = $(LIB_SRC:.c=.o)

TEST_SRC = $(wildcard tests/*.c) tests.c
TEST_OBJ = $(TEST_SRC:.c=.o)

all: $(LIB)

$(LIB): $(OBJ)
	ar rcs $(LIB) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(LIB) $(TEST_OBJ)
	$(CC) $(TEST_OBJ) $(LIB) -o test_runner $(LDFLAGS)
	./test_runner

gcov_report: CFLAGS += --coverage
gcov_report: LDFLAGS += --coverage
gcov_report: clean test
	rm -rf report
	mkdir -p report
	gcovr -r . \
	--html --html-details -o report/index.html \
	--filter 'functions/' \
	--exclude '.*/test.c'
	@echo "Report generated in report/index.html"

rebuild: clean all

cppcheck: $(LIB_SRC) $(LIB)
	cppcheck --check-level=exhaustive --enable=all --suppress=missingIncludeSystem $(LIB_SRC) $(LIB)


clean:
	rm -rf $(OBJ) $(TEST_OBJ) $(LIB) test_runner
	rm -rf *.gcda *.gcno *.info
	rm -rf tests/*.gcda  functions/*.gcda  tests/*.gcno  functions/*.gcno
	rm -rf report

style:
	clang-format -n functions/*.c *.h *.c tests/*.c
valgrind:
	valgrind --tool=memcheck  --leak-check=full ./test_runner 

clang:
	clang-format -i functions/*.c *.h *.c tests/*.c