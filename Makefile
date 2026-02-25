ifeq ($(OS), Windows_NT)
    # WINDOWS SETTINGS
	EXEC := a.exe
    STATIC_LIBS := src/lib/win64/libraylib.a
    INCLUDES := -I src/lib/include/
    LINK := -lopengl32 -lgdi32 -lwinmm -lshell32 -luser32 -lm
    RM := del /q
    CLEAN_PATH := src\main.o src\ecs\*.o src\gui\*.o src\core\*.o src\misc\*.o src\state\*.o $(EXEC)
    PLATFORM_FLAGS := -DRAYLIB_STATIC -D_WINDLL -D_AMD64_
else
    # LINUX SETTINGS
    EXEC := a.out
    STATIC_LIBS := src/lib/linux/libraylib.a
    INCLUDES := -I src/lib/include/
    LINK := -L src/lib/linux/ -lraylib -lm
    RM := rm -f
    CLEAN_PATH := src/main.o src/ecs/*.o src/gui/*.o src/core/*.o src/misc/*.o src/state/*.o $(EXEC)
    PLATFORM_FLAGS := 
endif

CXX := gcc
CXXFLAGS := -std=c99 $(PLATFORM_FLAGS) -Wall

SRCS := src/main.c $(wildcard src/gui/*.c src/core/*.c src/misc/*.c src/state/*.c src/ecs/*.c)
OBJS := $(SRCS:.c=.o)

%.o: %.c
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) $(STATIC_LIBS) -o $(EXEC) $(LINK)

clean:
	$(RM) $(CLEAN_PATH)
