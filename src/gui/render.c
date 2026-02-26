#include "window.h"
#include "shaders.h"
#include "../misc/math.h"
#include "raylib.h"
#include "mesh.h"

#include <math.h>
#include <stdio.h>

void draw_pixel(float x, float y, int r, int g, int b) { 
  DrawRectangle(x, y, 1, 1, (Color) {r,g,b,255});
}

void draw_line(float x1, float y1, float x2, float y2, int r, int g, int b) {
	DrawLine(x1, y1, x2, y2, (Color){r, g, b, 255});
}

WyrdMesh wmesh;
Model model = {0};
Texture2D tex = {0};

void render_3D(Window *win) {
	float px = win->ecs->position[0].x;
	float py = win->ecs->position[0].y + 2.0;
	float pz = win->ecs->position[0].z;
	
	float theta = win->ecs->direction[0].y;
	float phi = win->ecs->direction[0].z;
	float tx = sin(theta);
	float tz = cos(theta);
	float ty = sin(phi); //cos(win->ecs->direction[0].x) + cos(win->ecs->direction[0].z);

	win->cam3.position = (Vector3) {px, py, pz};
	win->cam3.target = (Vector3) {tx + px, py+ty, tz + pz};
	win->cam3.up = (Vector3){0.0f, 1.0f, 0.0f};
	win->cam3.fovy = 60; // Assign FOV value later
	win->cam3.projection = CAMERA_PERSPECTIVE;

	UpdateCamera(&win->cam3, CAMERA_CUSTOM);
	
	ClearBackground(BLACK);
	
	BeginMode3D(win->cam3);

	// Render 3d scene here
	DrawGrid(10, 1.0f);
	if (win->shred_flag) {
		shred_map(win->engine->world, &wmesh);

		Mesh mesh = { 0 };
		mesh.triangleCount = wmesh.triangle_count;
		mesh.vertexCount = wmesh.triangle_count*3;
		mesh.vertices = (float *)MemAlloc(1 + mesh.vertexCount*3*sizeof(float));    
		mesh.texcoords = (float *)MemAlloc(mesh.vertexCount*2*sizeof(float)); 
		mesh.normals = (float *)MemAlloc(mesh.vertexCount*3*sizeof(float));
		
		int vcount = wmesh.triangle_count*9;
		for(int i = 0; i < vcount; i++) {
			mesh.vertices[i] = (float) wmesh.vertex_array[i];

		}
		
		tex = LoadTexture("res/years.bmp");
		int tcount = wmesh.triangle_count*6;

		for(int j = 0; j < tcount; j++) {
			mesh.texcoords[j] = (float) wmesh.texture_coord_array[j];
		}

		UploadMesh(&mesh, true);
		model = LoadModelFromMesh(mesh);
		model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = tex;
		win->shred_flag = 0;
	} else {
		DrawModel(model, (Vector3){0.0f, 0.0f, 0.0f}, 1.0f, WHITE);
	}

	EndMode3D();
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
	}
	EndMode2D();
}
