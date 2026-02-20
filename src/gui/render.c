#include "window.h"
#include "shaders.h"
#include "glad/glad.h"
#include "../misc/math.h"

#include <GL/gl.h>
#include <math.h>
#include <stdio.h>


unsigned int pixel_shader;
unsigned int shader_3D;
unsigned int p_VAO, p_VBO;
unsigned int VAO, VBO;

void render_3D(Window *win) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glUseProgram(shader_3D);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void init_3D() {
	glGenBuffers(1, &VBO);  
	glBindBuffer(GL_ARRAY_BUFFER, VBO);  
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	unsigned int v_shader;
	v_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(v_shader, 1, &vertex_shader, NULL);
	glCompileShader(v_shader);

	int success;
	char info_log[512];
	glGetShaderiv(v_shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		printf("Problem compiling vertex shader:\n%s\n", info_log);
	}

	
	unsigned int f_shader;
	f_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(f_shader, 1, &fragment_shader, NULL);
	glCompileShader(f_shader);

	// Create shader program
	shader_3D = glCreateProgram();
	
	glAttachShader(shader_3D, v_shader);
	glAttachShader(shader_3D, f_shader);
	glLinkProgram(shader_3D);

	
	glGetProgramiv(shader_3D, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(shader_3D, 512, NULL, info_log);
		printf("Problem compiling shaders:\n%s\n", info_log);
	}

	// Cleanup
	glUseProgram(shader_3D);
	glDeleteShader(v_shader);
	glDeleteShader(f_shader);

	/*
	// VBO
	// Link vertex attribs
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// then set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);  
	// use our shader program when we want to render an object
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	*/
	glGenVertexArrays(1, &VAO); 
	// VAO
	// 1. bind Vertex Array Object
	glBindVertexArray(VAO);
	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);  
	// 4. draw the object

}

void init_pixel() {
  int success;
  char infoLog[512];

  // Compile Vertex Shader
  unsigned int p_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(p_vertex_shader, 1, &pixel_vertex_shader, NULL);
  glCompileShader(p_vertex_shader);
  
  // Check for errors
  glGetShaderiv(p_vertex_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
      glGetShaderInfoLog(p_vertex_shader, 512, NULL, infoLog);
      printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
  }

  // Compile Fragment Shader
  unsigned int p_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(p_fragment_shader, 1, &pixel_fragment_shader, NULL);
  glCompileShader(p_fragment_shader);
  
  // Check for errors
  glGetShaderiv(p_fragment_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
      glGetShaderInfoLog(p_fragment_shader, 512, NULL, infoLog);
      printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
  }

  // Link Shaders into Program
  pixel_shader = glCreateProgram();
  glAttachShader(pixel_shader, p_vertex_shader);
  glAttachShader(pixel_shader, p_fragment_shader);
  glLinkProgram(pixel_shader);
  
  // Check for linking errors
  glGetProgramiv(pixel_shader, GL_LINK_STATUS, &success);
  if (!success) {
      glGetProgramInfoLog(pixel_shader, 512, NULL, infoLog);
      printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
  }

  // Cleanup individual shaders
  glDeleteShader(p_vertex_shader);
  glDeleteShader(p_fragment_shader);

  // 5. Setup Vertex Data (The Dot)
  float vertices[] = { 0.0f, 0.0f }; // NDC Center

  glGenVertexArrays(1, &p_VAO);
  glGenBuffers(1, &p_VBO);

  glBindVertexArray(p_VAO);
  glBindBuffer(GL_ARRAY_BUFFER, p_VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Position attribute
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0); 
  glBindVertexArray(0); 
}

void draw_pixel(int x, int y, int width, int height) {
    glUseProgram(pixel_shader);

    // Get uniform locations
    int resLoc = glGetUniformLocation(pixel_shader, "u_resolution");
    int posLoc = glGetUniformLocation(pixel_shader, "u_position");

    // Send the window size and the target pixel to the shader
    glUniform2f(resLoc, (float)width, (float)height);
    glUniform2f(posLoc, (float)x, (float)y);

    // Draw the point
    glPointSize(5.0f); // Set dot size
    glBindVertexArray(p_VAO);
    glDrawArrays(GL_POINTS, 0, 1);
    glBindVertexArray(0);
}

void init_gl() {
	init_3D();
	init_pixel();
}
