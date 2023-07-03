CARGS = gcc -g -Wall -Werror -Wextra -std=c11 -pedantic
GCOVFLAGS = -fprofile-arcs -ftest-coverage
APP = build/Calculator.app
APP_ARCHIVE = Archive_Calculator_v1.0

OS = $(shell uname)
ifeq ($(OS), Linux)
	CHECK_FLAGS = -lpthread -lcheck -pthread -lrt -lm -lsubunit
else
	CHECK_FLAGS = -lcheck
endif

ifeq ($(OS),Linux)
	OPEN_CMD = xdg-open
endif
ifeq ($(OS),Darwin)
	OPEN_CMD = open
endif

.PHONY: dvi all install

all: install

test: calc_backend.a
	$(CARGS) test/*.c calc_backend.a $(CHECK_FLAGS) -o unit_test
	./unit_test

gcov_report: calc_backend.a
	$(CARGS) $(GCOVFLAGS) test/*.c backend/*.c $(CHECK_FLAGS) -o gcov_test
	./gcov_test
	gcov *.c
	gcov testc/*.c
	lcov -t "test" -o test.info -c -d .
	genhtml -o report/ test.info
	rm -rf *.o *.gcno *.gcda 
	$(OPEN_CMD) ./report/index.html

build:
	mkdir build
	cd build/ && qmake ../QT/smartcalc.pro && make

install: build
	@mkdir $(HOME)/Desktop/SmartCalc_v1.0/
	@cp -rf $(APP) $(HOME)/Desktop/SmartCalc_v1.0/
	make clean


calc_backend.a:
	$(CARGS) -c backend/*.c
	ar rcs calc_backend.a *.o
	rm -rf *.o
	 
run: install open

opencalc:
ifeq ($(OS), Darwin)
	open $(HOME)/Desktop/SmartCalc_v1.0/Calculator.app
else
	./build/Calculator.app	
endif

uninstall:
	@rm -rf $(HOME)/Desktop/SmartCalc_v1.0/

dvi:
	open Calculator.html

dist:
	mkdir -p SmartCalc_v1.0/src/
	cp -r backend QT test Calculator.html Makefile SmartCalc_v1.0/src/
	tar cvzf SmartCalc_v1.0.tgz SmartCalc_v1.0/
	mv SmartCalc_v1.0.tgz $(HOME)/Desktop/
	rm -rf SmartCalc_v1.0/

clang:
	clang-format -style=Google -n test/* backend/* QT/credit.cpp QT/credit.h QT/graph.cpp QT/graph.h  QT/main*.cpp QT/main*.h

clang-fix:
	clang-format -style=Google -i test/* backend/* QT/credit.cpp QT/credit.h QT/graph.cpp QT/graph.h  QT/main*.cpp QT/main*.h

leaks: test
	CK_FORK=no leaks --atExit -- ./unit_test

brew:
	cd ~
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh

lcov:
ifeq ($(OS),Linux)
	sudo apt install lcov
endif
ifeq ($(OS),Darwin)
	brew install lcov
endif

valgrind: test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./unit_test

clean:
	rm -rf build*
	rm -rf *.o *.gcno *.gcda *.a *.info report .clang-format *.out *.dSYM *.tgz
	rm -rf $(APP_ARCHIVE)/
	rm -f unit_test
	rm -f gcov_test
	rm -f out
	rm -rf SmartCalc_v1.0
