#ifndef SHADERS_H
#define SHADERS_H

/*
const char *vertex_shader = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "uniform mat4 model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "void main() {\n"
    "    gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
    "}\0";
*/ 
const char *vertex_shader = 
	"#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

const char *fragment_shader = 
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "    FragColor = vec4(0.0, 1.5, 0.5, 1.0);\n"
    "}\0";

	
const char *pixel_vertex_shader = 
	"#version 330 core\n"
	"layout (location = 0) in vec2 aPos;\n"
	"uniform vec2 u_resolution;\n" // Window width/height
	"uniform vec2 u_position;\n"   // Target pixel (x, y)
	"void main() {\n"
	"   // Convert pixel coordinates to NDC (-1 to 1)\n"
	"   vec2 ndc = (u_position / u_resolution) * 2.0 - 1.0;\n"
	"   // Flip Y because screen pixels start top-left, OpenGL starts bottom-left\n"
	"   gl_Position = vec4(ndc.x, -ndc.y, 0.0, 1.0);\n"
	"}\0";

const char *pixel_fragment_shader = 
	"#version 330 core\n"
   "out vec4 FragColor;\n"
   "void main() { FragColor = vec4(0.0, 1.0, 1.0, 1.0); }\0"; 

const char *line_vertex_shader = 
    "#version 330 core\n"
    "layout (location = 0) in vec2 aPos;\n"
    "uniform vec2 u_resolution;\n"
    "void main() {\n"
    "    // Convert pixel space (0,0 to width,height) to (0,0 to 1,1)\n"
    "    vec2 zeroToOne = aPos / u_resolution;\n"
    "    // Convert to (0,0 to 2,2)\n"
    "    vec2 zeroToTwo = zeroToOne * 2.0;\n"
    "    // Convert to (-1,-1 to 1,1) NDC\n"
    "    vec2 clipSpace = zeroToTwo - 1.0;\n"
    "    // Flip Y-axis so 0 is top and 'height' is bottom\n"
    "    gl_Position = vec4(clipSpace.x, -clipSpace.y, 0.0, 1.0);\n"
    "}\0";

const char *line_fragment_shader = 
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 u_color;\n"
    "void main() {\n"
    "    FragColor = u_color;\n"
    "}\0";

/*
float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};*/
float vertices[] = {
    // Back face
    -0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f, -0.5f,
    // Front face
    -0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f, -0.5f,  0.5f,
    // Left face
    -0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f,
    // Right face
     0.5f,  0.5f,  0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f,
    // Bottom face
    -0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f,
    // Top face
    -0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f
};

int vertc = 108;

#endif
