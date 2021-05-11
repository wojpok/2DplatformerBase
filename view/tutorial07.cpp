// Include standard headers
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;

GLuint t[3];
GLuint TransID;
GLuint billboard_vertex_buffer;
GLuint billboard_uv_buffer;
#include "utility.hpp"
class box {
	void clear() {
		glDeleteBuffers(1, &vertexBuffer);
		glDeleteBuffers(1, &uvBuffer);
		glDeleteProgram(programID);
		glDeleteTextures(1, &Texture);
    }
};

box* boxes[256];

extern int blockInd;

static void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        double x;
        double y;
        glfwGetCursorPos(window, &x, &y);
        //printf("Click at: %f %f\n", x, y);
        if(x <= 767 && x >= 221 && y <= 678 && y >= 129) {
			int xInd = (x-221)/(767-221)*16;
			int yInd = (y-129)/(678-129)*16;
			//printf( "%d %d\n",xInd-1, 15-yInd);
			boxes[xInd + (15-yInd)*16]->Texture = t[blockInd];
		}
    }
}

int main( void )
{



	GLuint programID = LoadShaders( "TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader" );
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	//TransID = glGetUniformLocation(programID, "trans");
	GLuint Texture = loadBMP_custom("simplegrass.bmp");
	GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");

	// Load it into a VBO
	static const GLfloat g_vertex_buffer_data[] = { 
		 0, -1, 1,
		 0, 1, -1,
		 0, -1, -1,
		 0, -1, 1,
		 0, 1, 1,
		 0, 1, -1,
	};
	
	glGenBuffers(1, &billboard_vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_DYNAMIC_DRAW);
	
	static const GLfloat g_uv_buffer_data[] = { 
		 1, -1,
		 0, 0,
		 0, -1,
		 1, -1,
		 1, 0,
		 0, 0
	};
	
	glGenBuffers(1, &billboard_uv_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, billboard_uv_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_DYNAMIC_DRAW);
	
	for(int i = 0 ; i < 256; i ++ )
		boxes[i] = new box( programID, MatrixID, Texture, TextureID);
	
	t[0] = Texture;
	t[1] = loadBMP_custom("simpledirt.bmp");
	t[2] = loadBMP_custom("simplestone.bmp");
	
	double x = 0, dx = 0.001;
	
	extern float deltaTime;
	
	do{
		computeMatricesFromInputs(window);
		x += deltaTime;
			
		// Clear the screen
		

		// Compute the MVP matrix from keyboard and mouse input
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		glm::mat4 ModelMatrix = glm::mat4(1);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		MVP = glm::scale(MVP, glm::vec3(0.125f, 0.125f, 0.125f));
		
		
		
			for(int i = 0 ; i < 256; i ++ ){
				boxes[i]->draw(glm::translate(MVP, glm::vec3(0 , (i>>4)*2, 2*(i&0xF))));
				boxes[i]->enableBuffers();}
		// Swap buffers


	// Cleanup VBO and shader
	glDeleteVertexArrays(1, &VertexArrayID);
	for(int i = 0 ; i < 10; i ++ )
			boxes[i]->clear();
	// Close OpenGL window and terminate GLFW


	return 0;
}

