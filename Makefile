ifeq ($(OS), Windows_NT)
    EXEC := a.exe
    SDL_PATH :=C:/msys64/mingw64
    
    INCLUDES := -Isrc/glad/include -I$(SDL_PATH)/include/SDL2
    LIBS := -L$(SDL_PATH)/lib -lmingw32 -lSDL2main -lSDL2 -mconsole
    RM := del /q
    CLEAN_PATH := src\main.o src\gui\*.o src\core\*.o src\utils\*.o src\state\*.o $(EXEC)
else
    # LINUX SETTINGS
    EXEC := a.out
    INCLUDES := -Isrc/glad/include
    LIBS := -L/usr/local/lib -lSDL2 -lSDL2main -lm -lpthread -lrt
    RM := rm -f
    CLEAN_PATH := src/main.o src/gui/*.o src/core/*.o src/utils/*.o src/state/*.o $(EXEC)
endif

CXX := gcc
CXXFLAGS := -std=c99

SRCS := src/main.c $(wildcard src/gui/*.c src/core/*.c src/utils/*.c src/state/*.c)
OBJS := $(SRCS:.c=.o)

%.o: %.c
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(INCLUDES) $(LIBS)

clean:
	$(RM) $(CLEAN_PATH)
