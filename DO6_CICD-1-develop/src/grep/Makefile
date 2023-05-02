TARGET = s21_grep

CC = gcc -Wall -Werror -Wextra

all : $(TARGET) clean

$(TARGET).o : $(TARGET).c $(TARGET).h
	$(CC) -c $(TARGET).c 

$(TARGET) : $(TARGET).o
	$(CC) -o $(TARGET) $(TARGET).o

rebuild : clean all		

clean :
	rm -f $(TARGET).o

testfunc :
	 ./test_func_grep.sh 2>../testfunc_grep.log 1> ../testfunc_grep.log

testleak : 
	./test_leak_grep.sh

style :
	clang-format -n $(TARGET).* 2>> ../style.log