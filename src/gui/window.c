#include "window.h"
#include "glad/glad.h"
#include "../misc/input_map.h"

#include <GL/gl.h>

unsigned int pixel_shader;
unsigned int VAO, VBO;

void init_pixel() {
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec2 aPos;\n"
		"uniform vec2 u_resolution;\n" // Window width/height
		"uniform vec2 u_position;\n"   // Target pixel (x, y)
		"void main() {\n"
		"   // Convert pixel coordinates to NDC (-1 to 1)\n"
		"   vec2 ndc = (u_position / u_resolution) * 2.0 - 1.0;\n"
		"   // Flip Y because screen pixels start top-left, OpenGL starts bottom-left\n"
		"   gl_Position = vec4(ndc.x, -ndc.y, 0.0, 1.0);\n"
		"}\0";

  const char* fragmentShaderSource = "#version 330 core\n"
      "out vec4 FragColor;\n"
      "void main() { FragColor = vec4(1.0, 0.0, 0.0, 1.0); }\0"; // Red color

  int success;
  char infoLog[512];

  // Compile Vertex Shader
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  
  // Check for errors
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
      glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
      printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
  }

  // Compile Fragment Shader
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  
  // Check for errors
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
      glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
      printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
  }

  // Link Shaders into Program
  pixel_shader = glCreateProgram();
  glAttachShader(pixel_shader, vertexShader);
  glAttachShader(pixel_shader, fragmentShader);
  glLinkProgram(pixel_shader);
  
  // Check for linking errors
  glGetProgramiv(pixel_shader, GL_LINK_STATUS, &success);
  if (!success) {
      glGetProgramInfoLog(pixel_shader, 512, NULL, infoLog);
      printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
  }

  // Cleanup individual shaders
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // 5. Setup Vertex Data (The Dot)
  float vertices[] = { 0.0f, 0.0f }; // NDC Center

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Position attribute
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0); 
  glBindVertexArray(0); 
}

bool init_window(Window *win, char *title, int width, int height) {
	win->width = width;
	win->height = height;
	
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
	
	// Enable VSync
	if (SDL_GL_SetSwapInterval(1) < 0) {
		printf("Warning: Unable to set VSync! SDL_Error: %s\n", SDL_GetError());
	}
	
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		printf("Failed to initialize GLAD\n");
		return false;
	}

	// Init shaders
	init_pixel();

	// Window events
	win->quit_event = new_event(E_TERM, 0);
	win->forward_event = new_event(E_INPUT, I_FORWARD);
	win->backward_event = new_event(E_INPUT, I_BACKWARD);
	win->left_event = new_event(E_INPUT, I_STRAFE_LEFT);
	win->right_event = new_event(E_INPUT, I_STRAFE_RIGHT);
	win->jump_event = new_event(E_INPUT, I_JUMP);

	return true;
}

void swap_buffers(Window *win) {
	SDL_GL_SwapWindow(win->sdl_window);
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
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, 1);
    glBindVertexArray(0);
}

void handle_window_input(Window *win) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
	  switch (event.type) {
	    case SDL_QUIT:
				queue_event(win->em, win->quit_event);
	      break;
		}
	}
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
	
}

void draw_frame(Window *win) {
	// Set background color
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Add 3D rendering code here
  float x = win->ecs->position[0].x;
	float y = win->ecs->position[0].z;
	draw_pixel(x, y, win->width, win->height);
	// Swap the buffers
	swap_buffers(win);
	handle_window_input(win);
}


void close_window(Window *win) {
	SDL_GL_DeleteContext(win->gl_context);
	SDL_DestroyWindow(win->sdl_window);
	SDL_Quit();
}
