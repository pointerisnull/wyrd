compile:
	gcc src/*.c src/ui/*.c -L/usr/local/lib /usr/local/lib/libSDL2.a -lm -lpthread -lrt
