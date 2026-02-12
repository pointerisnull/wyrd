ifeq ($(OS), Windows_NT)
    # WINDOWS SETTINGS
	EXEC := a.exe
    SDL_PATH :=C:/msys64/mingw64
    
    INCLUDES := -Isrc/lib/glad/include -I$(SDL_PATH)/include/SDL2
    LIBS := -L$(SDL_PATH)/lib -lmingw32 -lSDL2main -lSDL2 -mconsole
    RM := del /q
    CLEAN_PATH := src\lib\glad\src\glad.o src\main.o src\gui\*.o src\core\*.o src\utils\*.o src\state\*.o $(EXEC)
else
    # LINUX SETTINGS
    EXEC := a.out

    INCLUDES := -Isrc/lib/glad/include
    LIBS := -L/usr/local/lib -lSDL2 -lSDL2main -lm -lpthread -lrt -ldl
    RM := rm -f
    CLEAN_PATH := src/lib/glad/src/glad.o src/main.o src/gui/*.o src/core/*.o src/utils/*.o src/state/*.o $(EXEC)
endif

CXX := gcc
CXXFLAGS := -std=c99

GLAD_PATH := src/lib/glad/src/glad.c

SRCS := src/main.c $(wildcard src/gui/*.c src/core/*.c src/utils/*.c src/state/*.c) $(GLAD_PATH)
OBJS := $(SRCS:.c=.o)

%.o: %.c
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(INCLUDES) $(LIBS)

clean:
	$(RM) $(CLEAN_PATH)
