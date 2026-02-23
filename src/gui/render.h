#ifndef RENDER_H
#define RENDER_H

#include "window.h"

void init_gl();
void draw_pixel(int x, int y, int width, int height);
void draw_line(float x1, float y1, float x2, float y2, int width, int height);
void render_3D(Window *win);

#endif
