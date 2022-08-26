CC = g++
I_FLAGS = -ILOG -Iinclude

all:  
	$(CC) main.cpp LOG/lib/Log.o StrAlgorithm.cpp $(I_FLAGS) -o main.exe