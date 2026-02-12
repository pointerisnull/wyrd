#include "window.h"
#include "glad/glad.h"

#include <GL/gl.h>

bool init_window(Window *win, char *title, int width, int height) {
	win->width = width;
	win->height = height;
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	
	win->sdl_window = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width,
		height,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
	);
	
	if (!win->sdl_window) {
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	
	win->gl_context = SDL_GL_CreateContext(win->sdl_window);
	if (!win->gl_context) {
		printf("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	
	// Enable VSync
	if (SDL_GL_SetSwapInterval(1) < 0) {
		printf("Warning: Unable to set VSync! SDL_Error: %s\n", SDL_GetError());
	}
	
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		printf("Failed to initialize GLAD\n");
		return false;
	}

	return true;
}

void draw_frame(Window *win) {
	//char *path = "./res/years.bmp";

	// Set background color
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Add 3D rendering code here
	
	// Swap the buffers
	SDL_GL_SwapWindow(win->sdl_window);
}

void close_window(Window *win) {
	SDL_GL_DeleteContext(win->gl_context);
	SDL_DestroyWindow(win->sdl_window);
	SDL_Quit();
}
