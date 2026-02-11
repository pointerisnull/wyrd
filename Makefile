ifeq ($(OS), Windows_NT)
<<<<<<< HEAD
    EXEC := a.exe
    
	SDL_PATH := C:/msys64/mingw64/include/SDL2
    
    INCLUDES := -Isrc/glad/include -I$(SDL_PATH)/include
    LIBS := -L$(SDL_PATH)/lib -lmingw32 -lSDL2main -lSDL2 -mconsole
    RM := del /q
    # Fix backslashes for the RM command on Windows
    CLEAN_PATH := src\main.o src\ui\*.o src\engine\*.o $(EXEC)
else # Linux
    EXEC := a.out
    INCLUDES := -Isrc/glad/include
    LIBS := -L/usr/local/lib -lSDL2 -lm -lpthread -lrt
    RM := rm -f
    CLEAN_PATH := src/main.o src/ui/*.o src/engine/*.o $(EXEC)
endif

CXX := gcc
CXXFLAGS := -std=c99

SRCS := src/main.c $(wildcard src/ui/*.c src/engine/*.c)
=======
    # WINDOWS SETTINGS
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
>>>>>>> engine
OBJS := $(SRCS:.c=.o)

%.o: %.c
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(INCLUDES) $(LIBS)

clean:
<<<<<<< HEAD
	$(RM) $(CLEAN_PATH)
=======
	$(RM) $(CLEAN_PATH)
>>>>>>> engine
