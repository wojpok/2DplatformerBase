// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

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
public:
	GLuint vertexBuffer;
	GLuint uvBuffer;
	GLuint programID;
	GLuint MatrixID;
	GLuint Texture;
	GLuint TextureID;
	int vsize;
	
	int counter;
	
	box(
		GLuint programID,
		GLuint MatrixID,
		GLuint Texture,
		GLuint TextureID) {

		vertexBuffer = billboard_vertex_buffer;	
		uvBuffer = billboard_uv_buffer;
	
		this->programID = programID;
		this->MatrixID = MatrixID;
		this->Texture = Texture;
		this->TextureID = TextureID;
		this->vsize = 6;
	}
	
	void enableBuffers() {
		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(
			0,                  // attribute
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glVertexAttribPointer(
			1,                                // attribute
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);
		glDrawArrays(GL_TRIANGLES, 0, vsize );

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}
	
	void draw(glm::mat4 MVP) {
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		//glUniform1f(TransID, 0.9);
		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		// Set our "myTextureSampler" sampler to use Texture Unit 0
		glUniform1i(TextureID, 0);	
	}
	
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
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024, 768, "Tutorial 07 - Model Loading", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Hide the mouse and enable unlimited mouvement
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    glfwSetMouseButtonCallback(window, mouse_callback);
    
    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, 1024/2, 768/2);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

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
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

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
		glfwSwapBuffers(window);
		glfwPollEvents();
	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO and shader
	glDeleteVertexArrays(1, &VertexArrayID);
	for(int i = 0 ; i < 10; i ++ )
			boxes[i]->clear();
	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

