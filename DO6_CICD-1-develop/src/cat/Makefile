TARGET = s21_cat

.PHONY : all clean $(TARGET).o $(TARGET) rebuild testfunc testleak clangtest

CC = gcc -Wall -Werror -Wextra

all : $(TARGET) clean

$(TARGET).o : $(TARGET).c $(TARGET).h
	$(CC) -c $(TARGET).c 

$(TARGET) : $(TARGET).o
	$(CC) -o $(TARGET) $(TARGET).o

rebuild : clean all		

clean :
	rm $(TARGET).o

testfunc :
	 ./test_func_cat.sh

testleak : 
	./test_leak_cat.sh

style :
	clang-format -n $(TARGET).*	