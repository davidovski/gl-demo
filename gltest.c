#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

static const int width = 1280;
static const int height = 720;

static GLuint vertexbuffer;


int init_vert() {
	// array of 3 vectors, each one a vertex
	GLfloat g_vertex_buffer_data[] = {
	   -1.0f, -1.0f, 0.0f,
	   1.0f, -1.0f, 0.0f,
	   0.0f,  1.0f, 0.0f,
	};
	
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

}


int draw_triangle() {
	// first attribute buffer: vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,		// attribute 0
		3,		// size of buffer
		GL_FLOAT,	// type
		GL_FALSE,	// NORMALISE
		0,		// stride
		(void*)0		// buffer offset
	);
	// draw the triangle
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0); // end the attribute array

}


int loop(GLFWwindow* window) {
	// keep doing things until 
	while (glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {
		glClear(GL_COLOR_BUFFER_BIT);

		draw_triangle();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

int main() {
	
	if (glfwInit() == GLEW_OK) {
		fprintf(stderr, "Failed to init GLFW\n");
		return 1;
	}
	
	// create hints for the window
	glfwWindowHint(GLFW_SAMPLES, 4); // antialiasing
	// Ask for version 3.3 of gl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// needed for macos compatibility, no other reason
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
	// don't use old opengl
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // core profile

	// actually open the window
	GLFWwindow* window;
	window = glfwCreateWindow(width, height, "OpenGL test", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed creating the GLFW window!");
		glfwTerminate();
		return 1;
	}
	
	// init glfw
	glfwMakeContextCurrent(window);
	
	init_vert();
	// capture keys for the window
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	loop(window);
	return 0;
}
