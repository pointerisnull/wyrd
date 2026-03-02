#include "window.h"
#include "render.h"
#include "../misc/input_map.h"
#include "../core/world.h"
#include "raylib.h"

#include <math.h>

bool init_window(Window *win, char *title, int width, int height) {
	win->width = width;
	win->height = height;
	win->mode = WM_2D;
	win->shred_flag = 0;

	win->cam2 = (Camera2D){0};
	win->cam3 = (Camera3D){0};

	//SetTargetFPS(fps);
	SetTraceLogLevel(LOG_ERROR); 
	InitWindow(width, height, title);
	HideCursor();

	// Window events
	win->quit_event = new_event(E_TERM, 0);
	win->forward_event = new_event(E_INPUT, I_FORWARD);
	win->backward_event = new_event(E_INPUT, I_BACKWARD);
	win->left_event = new_event(E_INPUT, I_STRAFE_LEFT);
	win->right_event = new_event(E_INPUT, I_STRAFE_RIGHT);
	win->look_left_event = new_event(E_INPUT, I_YAW_LEFT);
	win->look_right_event = new_event(E_INPUT, I_YAW_RIGHT);
	win->look_up_event = new_event(E_INPUT, I_PITCH_UP);
	win->look_down_event = new_event(E_INPUT, I_PITCH_DOWN);
	win->jump_event = new_event(E_INPUT, I_JUMP);
	win->sprint_event = new_event(E_INPUT, I_SPRINT);
	win->slow_event = new_event(E_INPUT, I_WALK);
	
	init_3D(win);

	return true;
}

void handle_window_input(Window *win) {
	if(IsKeyDown(KEY_H))
		queue_event(win->em, win->look_left_event);
	
	if(IsKeyDown(KEY_L)) 
		queue_event(win->em, win->look_right_event);
	
	if(IsKeyDown(KEY_J)) 
		queue_event(win->em, win->look_down_event);
	
	if(IsKeyDown(KEY_K)) 
		queue_event(win->em, win->look_up_event);
	
	if(IsKeyDown(KEY_W)) 
		queue_event(win->em, win->forward_event);
	
	if(IsKeyDown(KEY_S)) 
		queue_event(win->em, win->backward_event);
	
	if(IsKeyDown(KEY_D)) 
		queue_event(win->em, win->right_event);
	
	if(IsKeyDown(KEY_A)) 
		queue_event(win->em, win->left_event);
	
	if(IsKeyDown(KEY_SPACE))
		queue_event(win->em, win->jump_event);
	
	if(IsKeyPressed(KEY_LEFT_SHIFT))
		queue_event(win->em, win->sprint_event);
	
	if(IsKeyReleased(KEY_LEFT_SHIFT))
		queue_event(win->em, win->slow_event);

	if(IsKeyPressed(KEY_F))
		ToggleFullscreen();
	
	if(IsKeyPressed(KEY_Q))
		queue_event(win->em, win->quit_event);
	
	if(IsKeyPressed(KEY_M))
		win->mode = (win->mode == WM_2D) ? WM_3D : WM_2D;
	
	if(IsKeyPressed(KEY_V))
		win->shred_flag = 1;

}

void draw_frame(Window *win) {
	BeginDrawing();
	
	// Set background color
	ClearBackground(BLACK);
	
	// Render Scene
	switch (win->mode) {
		case WM_3D:
			render_3D(win);
			break;
		case WM_2D:
			render_2D(win);
			break;
		default:
			break;
	}
	
	DrawText("Wyrd Engine - indev", 5, 0, 10, LIGHTGRAY);
	DrawText("--------------------", 5, 10, 5, LIGHTGRAY);
	DrawText(TextFormat("x: %f\ny: %f\nz: %f", win->ecs->position[0].x, win->ecs->position[0].y, win->ecs->position[0].z), 5, 20, 10, LIGHTGRAY);

	handle_window_input(win);
	EndDrawing();
}

void close_window(Window *win) {

	clear_3D();
	CloseWindow();
}
