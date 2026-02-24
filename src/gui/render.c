#include "window.h"
#include "shaders.h"
#include "../misc/math.h"
#include "raylib.h"

#include <math.h>
#include <stdio.h>

void draw_pixel(float x, float y, int r, int g, int b) { 
  DrawRectangle(x, y, 1, 1, (Color) {r,g,b,255});
}

void draw_line(float x1, float y1, float x2, float y2, int r, int g, int b) {
	DrawLine(x1, y1, x2, y2, (Color){r, g, b, 255});
}

void render_3D(Window *win) {

}

void render_2D(Window *win) {
	float zoom_factor = 2.0f;
	float x = win->ecs->position[0].x;
	float y = win->ecs->position[0].z;
	float theta = win->ecs->direction[0].y;
	float tx = x + 5*sin(theta);
	float ty = y + 5*cos(theta);
	
	win->cam2.target = (Vector2){x-(win->width/(zoom_factor*2)), y-(win->height/(zoom_factor*2))};
	win->cam2.zoom = zoom_factor;

	BeginMode2D(win->cam2);

	// draw user
	//draw_pixel(x, y, 255, 0, 255);
	//draw_pixel(win->width/2, win->height/2, win->width, win->height);
	//draw_pixel(tx, ty, 255, 0, 255);
	draw_line(x, y, tx, ty, 0, 255, 255);
	World *w = win->engine->world;
	Vertex *v = w->v;
	Line *l = w->l;
	for (int i = 0; i < w->lc; i++) {
		float hx = (v[l[i].head].x);
		float hz = (v[l[i].head].z);
		float tx = (v[l[i].tail].x);
		float tz = (v[l[i].tail].z);
		draw_line(hx, hz, tx, tz, 255, 0, 255);
		//draw_pixel(hx, hz, 0, 255, 255);
		//draw_pixel(tx, tz, 0, 255, 255);
	}
	EndMode2D();
}
