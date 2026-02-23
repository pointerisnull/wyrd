#include "window.h"
#include "render.h"
#include "glad/glad.h"
#include "../misc/input_map.h"
#include "../core/world.h"

#include <GL/gl.h>
#include <math.h>

bool init_window(Window *win, char *title, int width, int height) {
	win->width = width;
	win->height = height;
	win->mode = WM_3D;
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	
	// Version stuff
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	
	// Coloring. Allocates AT LEAST N bits for each
	int N = 8;
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, N);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, N);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, N);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, N);
	
	//SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 32);
	// Allocates space for two windows. Renders one frame while the other is being drawn
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


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
	
	// Create a new context for OpenGL
	win->gl_context = SDL_GL_CreateContext(win->sdl_window);

	if (!win->gl_context) {
		printf("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	
	// VSync for OpenGL
	bool enable_vsync = true;
	SDL_GL_SetSwapInterval(enable_vsync);
	
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		printf("Failed to initialize GLAD\n");
		return false;
	}

	// Init shaders
	init_gl();

	// Window events
	win->quit_event = new_event(E_TERM, 0);
	win->forward_event = new_event(E_INPUT, I_FORWARD);
	win->backward_event = new_event(E_INPUT, I_BACKWARD);
	win->left_event = new_event(E_INPUT, I_STRAFE_LEFT);
	win->right_event = new_event(E_INPUT, I_STRAFE_RIGHT);
	win->look_left_event = new_event(E_INPUT, I_YAW_LEFT);
	win->look_right_event = new_event(E_INPUT, I_YAW_RIGHT);
	win->jump_event = new_event(E_INPUT, I_JUMP);

	return true;
}

void swap_buffers(Window *win) {
	SDL_GL_SwapWindow(win->sdl_window);
}

void handle_window_input(Window *win) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
	  switch (event.type) {
	    case SDL_QUIT:
			queue_event(win->em, win->quit_event);
			break;
		case SDL_KEYUP: // Handle discrete key presses here
			if (event.key.keysym.sym == 110) { // N key
				win->mode = (win->mode == WM_2D) ? WM_3D : WM_2D;
			}
			break;
		}
	}
	// Handle non-discrete key inputs down here
	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	
	if (keystates[SDL_SCANCODE_SPACE])
		queue_event(win->em, win->jump_event);
	 
	if (keystates[SDL_SCANCODE_W])
		queue_event(win->em, win->forward_event);
	
	if (keystates[SDL_SCANCODE_S])
		queue_event(win->em, win->backward_event);
	
	if (keystates[SDL_SCANCODE_A])
		queue_event(win->em, win->left_event);
	
	if (keystates[SDL_SCANCODE_D])
		queue_event(win->em, win->right_event);

	if (keystates[SDL_SCANCODE_H])
		queue_event(win->em, win->look_left_event);

	if (keystates[SDL_SCANCODE_L])
		queue_event(win->em, win->look_right_event);
	
}

void draw_frame(Window *win) {
	// Set background color
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Add 3D rendering code here
	if (win->mode == WM_2D) {
		// screen x,y -> world space x,z
		float zoom_factor = 4.0f;
		float x = win->ecs->position[0].x;
		float y = win->ecs->position[0].z;
		float wx = 0-x;
		float wy = 0-y;
		float theta = win->ecs->direction[0].y;
		float tx = win->width/2 + 10*sin(theta);
		float ty = win->height/2 + 10*cos(theta);
		//draw_pixel(win->width/2, win->height/2, win->width, win->height);
		//draw_pixel(tx, ty, win->width, win->height);
		draw_line(win->width/2, win->height/2, tx, ty, win->width, win->height);
		World *w = win->engine->world;
		Vertex *v = w->v;
		Line *l = w->l;
		for (int i = 0; i < w->lc; i++) {
			float hx = (v[l[i].head].x+wx)*zoom_factor;
			float hz = (v[l[i].head].z+wy)*zoom_factor;
			float tx = (v[l[i].tail].x+wx)*zoom_factor;
			float tz = (v[l[i].tail].z+wy)*zoom_factor;
			draw_line(hx, hz, tx, tz, win->width, win->height);
			//draw_pixel((w->v[i].x+wx)*zoom_factor, (w->v[i].z+wy)*zoom_factor, win->width, win->height);
		}
		//draw_pixel(20*zoom_factor, 20*zoom_factor, win->width, win->height);
		//draw_pixel(20*zoom_factor, 30*zoom_factor, win->width, win->height);
	} else if (win->mode == WM_3D) {
		render_3D(win);
	}
	// Swap the buffers
	swap_buffers(win);
	handle_window_input(win);
}


void close_window(Window *win) {
	SDL_GL_DeleteContext(win->gl_context);
	SDL_DestroyWindow(win->sdl_window);
	SDL_Quit();
}
