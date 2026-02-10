CXX := gcc
CXXFLAGS := -std=c99 #-Wall #--static

LIBS := -L/usr/local/lib /usr/local/lib/libSDL2.a -lm -lpthread -lrt
INCLUDES := -I /src/glad/include

SRCS := src/main.c $(wildcard src/ui/*.c src/engine/*.c)
OBJS := $(SRCS:.c=.o)
EXEC := a.out

%.o: %.c
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) $(INCLUDES) -o $@ $(LIBS)

clean:
	rm -f src/main.o src/ui/*.o src/engine/*.o a.out
