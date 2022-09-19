ifeq ($(OS),Windows_NT)
	OUTPUT_FILE_NAME = main.exe
else
    	OUTPUT_FILE_NAME = main.out
endif

CC = g++
CFLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -D_DEBUG -D_EJUDGE_CLIENT_SIDE
IFLAGS = -I./LOG/ -I./include/ -I./OptionsCmdLine/

#main
SRC_DIR = ./src/
OBJ_DIR = ./lib/

SRC = $(wildcard $(SRC_DIR)*.cpp)
OBJ = $(patsubst $(SRC_DIR)%.cpp, $(OBJ_DIR)%.o, $(SRC)) 

#LOG
LOG_SRC_DIR = ./LOG/src/
LOG_OBJ_DIR = ./LOG/lib/

LOG_SRC = $(wildcard $(LOG_SRC_DIR)*.cpp)
LOG_OBJ = $(patsubst $(LOG_SRC_DIR)%.cpp, $(LOG_OBJ_DIR)%.o, $(LOG_SRC))

#Options command line
OPT_CMD_LINE_SRC_DIR = ./OptionsCmdLine/src/
OPT_CMD_LINE_OBJ_DIR = ./OptionsCmdLine/lib/

OPT_CMD_LINE_SRC = $(wildcard $(OPT_CMD_LINE_SRC_DIR)*.cpp)
OPT_CMD_LINE_OBJ = $(patsubst $(OPT_CMD_LINE_SRC_DIR)%.cpp, $(OPT_CMD_LINE_OBJ_DIR)%.o, $(OPT_CMD_LINE_SRC))

#linking
all : $(OBJ) $(LOG_OBJ) 
	$(CC) $(IFLAGS) $(CFLAGS) $^ -o $(OUTPUT_FILE_NAME)

#main
$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp
	mkdir -p $(@D)
	$(CC) $(IFLAGS) $(CFLAGS) -c $^ -o $@

#LOG
$(LOG_OBJ_DIR)%.o : $(LOG_SRC_DIR)%.cpp
	mkdir -p $(@D)
	$(CC) $(IFLAGS) $(CFLAGS) -c $^ -o $@

#Options command line
$(OPT_CMD_LINE_OBJ_DIR)%.o : $(OPT_CMD_LINE_SRC_DIR)%.cpp
	$(CC) $(IFLAGS) $(CFLAGS) -c $^ -o $@

clear: 
	rm -f $(OBJ_DIR)*.o
	rm -f $(LOG_OBJ_DIR)*.o
	rm -f $(OPT_CMD_LINE_OBJ)*.o