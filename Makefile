ifeq ($(OS), Windows_NT)
    # WINDOWS SETTINGS
	EXEC := a.exe
    SDL_PATH :=C:/msys64/mingw64
    
    INCLUDES := -Isrc/lib/glad/include -I$(SDL_PATH)/include/SDL2
    LIBS := -L$(SDL_PATH)/lib -lmingw32 -lSDL2main -lSDL2 -mconsole
    RM := del /q
    CLEAN_PATH := src\lib\glad\src\glad.o src\main.o src\ecs\*.o src\gui\*.o src\core\*.o src\misc\*.o src\state\*.o $(EXEC)
else
    # LINUX SETTINGS
    EXEC := a.out

    INCLUDES := -I src/lib/include/
    LIBS := -L src/lib -lraylib -lm
    RM := rm -f
    CLEAN_PATH := src/lib/glad/src/glad.o src/main.o src/ecs/*.o src/gui/*.o src/core/*.o src/misc/*.o src/state/*.o $(EXEC)
endif

CXX := gcc
CXXFLAGS := -std=c99

SRCS := src/main.c $(wildcard src/gui/*.c src/core/*.c src/misc/*.c src/state/*.c src/ecs/*.c)
OBJS := $(SRCS:.c=.o)

%.o: %.c
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(INCLUDES) $(LIBS)

clean:
	$(RM) $(CLEAN_PATH)
