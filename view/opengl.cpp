#include <cstdio>
#include <cstdlib>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>


#include "opengl.hpp"

namespace view {
	GLFWwindow* window;
	shape* block;
	
	void createContext() {
		if( !glfwInit() ) {
			fprintf( stderr, "Failed to initialize GLFW\n" );
			getchar();
			exit(1);
		}

		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// Open a window and create its OpenGL context
		window = glfwCreateWindow( 1600, 900, "2Dplatformer", NULL, NULL);
		if( window == NULL ){
			fprintf( stderr, "Failed to open GLFW window.\n" );
			getchar();
			glfwTerminate();
			exit(1);
		}
		glfwMakeContextCurrent(window);

		// Initialize GLEW
		glewExperimental = true; // Needed for core profile
		if (glewInit() != GLEW_OK) {
			fprintf(stderr, "Failed to initialize GLEW\n");
			getchar();
			glfwTerminate();
			exit(1);
		}
		
		glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
		//glfwSetMouseButtonCallback(window, mouse_callback);
		
		glfwPollEvents();
		glfwSetCursorPos(window, 1024/2, 768/2);

		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		
		//anti-aliasing
		glEnable(GL_MULTISAMPLE);  

		
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS); 
		glEnable(GL_CULL_FACE);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		GLuint VertexArrayID;
		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);
		
		// Load it into a VBO
		GLuint billboard_vertex_buffer, billboard_uv_buffer;
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
		
		//offsetting UV for easier atlas-texture-borders anti aliasing
		//set to 0 and see the difference
		float borderUV = 0.001f;
		
		/*static const GLfloat g_uv_buffer_data[] = { 
			 1 - UVoffset, -1 + UVoffset,
			 0+ UVoffset, 0- UVoffset,
			 0+ UVoffset, -1+ UVoffset,
			 1- UVoffset, -1+ UVoffset,
			 1- UVoffset, 0- UVoffset,
			 0+ UVoffset, 0- UVoffset
		};*/
		
		static const GLfloat g_uv_buffer_data[] = { 
			 1 - borderUV, 0 + borderUV,
			 0+ borderUV, 1- borderUV,
			 0+ borderUV, 0+ borderUV,
			 1- borderUV, 0+ borderUV,
			 1- borderUV, 1- borderUV,
			 0+ borderUV, 1- borderUV
		};
		
		glGenBuffers(1, &billboard_uv_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, billboard_uv_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_DYNAMIC_DRAW);
	
		block = new shape(billboard_vertex_buffer, billboard_uv_buffer, 6);
	}
	
	void clearFrame() {glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);}
	void pushFrame() {
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	bool isContextOpen() {
		return glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 ;
	}
	
	void clearContext() {
		glfwTerminate();
	}
	
	
	
	
	shape::shape(GLuint vb, GLuint ub, int bs) : vertexBuffer(vb), uvBuffer(ub), bufferSize(bs) { }
	
	void shape::draw() {
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
		glDrawArrays(GL_TRIANGLES, 0, bufferSize );
		
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}
	
	void shape::drawInstantiated( int count) {
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
		glDrawArrays(GL_TRIANGLES, 0, bufferSize );
		
		glVertexAttribDivisor(0, 0);
		glVertexAttribDivisor(1, 0); 
		
		glDrawArraysInstanced(GL_TRIANGLES, 0, bufferSize, count);
		
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}
	
	shape::~shape() {
		glDeleteBuffers(1, &vertexBuffer);
		glDeleteBuffers(1, &uvBuffer);
	}
	
	void shader::bindTexture(GLuint Texture) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		glUniform1i(TextureID, 0);
	}
	
	void shader::bindMVP(glm::mat4 MVP) {
		glUniformMatrix4fv(MVPID, 1, GL_FALSE, &MVP[0][0]);
	}
	
	void shader::bindPos(glm::mat4 Pos) {
		glUniformMatrix4fv(Pos1ID, 1, GL_FALSE, &Pos[0][0]);
	}
	void shader::bindPos2(glm::mat4 Pos) {
		glUniformMatrix4fv(Pos2ID, 1, GL_FALSE, &Pos[0][0]);
	}
	
	void shader::useProgram() {glUseProgram(Shader); }
}
