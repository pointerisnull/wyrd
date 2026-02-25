ifeq ($(OS), Windows_NT)
    # WINDOWS SETTINGS
	EXEC := a.exe
    
    INCLUDES := -I src/lib/include/
    LIBS := -lopengl32 -lgdi32 -lwinmm -lshell32 -luser32 -lm
    RM := del /q
    CLEAN_PATH := src\main.o src\ecs\*.o src\gui\*.o src\core\*.o src\misc\*.o src\state\*.o $(EXEC)
    PLATFORM_FLAGS := -DRAYLIB_STATIC -D_WINDLL -D_AMD64_
else
    # LINUX SETTINGS
    EXEC := a.out

    INCLUDES := -I src/lib/include/
    LIBS := -L src/lib -lraylib -lm
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
	$(CXX) $(OBJS) src/lib/libraylib.a -o $(EXEC) $(LIBS)

#$(EXEC): $(OBJS)
#	$(CXX) $(OBJS) -o $(EXEC) src/lib/libraylib.a $(LIBS)

clean:
	$(RM) $(CLEAN_PATH)
