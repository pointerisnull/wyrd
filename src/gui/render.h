#ifndef RENDER_H
#define RENDER_H

#include "window.h"

void init_gl();
void draw_pixel(float x, float y, int r, int g, int b);
void draw_line(float x1, float y1, float x2, float y2, int width, int height);
void render_3D(Window *win);

#endif
