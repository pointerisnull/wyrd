#ifndef RENDER_H
#define RENDER_H

#include "window.h"

void draw_pixel(float x, float y, int r, int g, int b);
void draw_line(float x1, float y1, float x2, float y2, int r, int g, int b);
void init_3D(Window *win);
void render_3D(Window *win);
void render_2D(Window *win);
void clear_3D();

#endif
