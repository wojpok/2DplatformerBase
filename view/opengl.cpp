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
	//GLFWwindow* window;
	//shape* block;
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
		window = glfwCreateWindow( 1024, 768, "2Dplatformer", NULL, NULL);
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
	
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;

	glm::mat4 getViewMatrix(){
		return ViewMatrix;
	}
	glm::mat4 getProjectionMatrix(){
		return ProjectionMatrix;
	}


	// Initial position : on +Z
	glm::vec3 position = glm::vec3( -4, 2, 2 ); 
	// Initial horizontal angle : toward -Z
	float horizontalAngle = 3.14/2;
	// Initial vertical angle : none
	float verticalAngle = 0.0f;
	// Initial Field of View
	float initialFoV = 70.0f;

	float speed = 20.0f; // 3 units / second
	float mouseSpeed = 0.005f;

	float deltaTime;

	int blockInd = 0;

	float getDeltaTime() {
		return deltaTime;
	}
	
	void computeMatricesFromInputs(){

		// glfwGetTime is called only once, the first time this function is called
		static double lastTime = glfwGetTime();

		// Compute time difference between current and last frame
		double currentTime = glfwGetTime();
		deltaTime = float(currentTime - lastTime);

		// Get mouse position
		double xpos = 0 , ypos = 0;
		glfwGetCursorPos(window, &xpos, &ypos);
		
		// Reset mouse position for next frame
		glfwSetCursorPos(window, 1024/2, 768/2);

		// Compute new orientation
		horizontalAngle += mouseSpeed * float(1024/2 - xpos );
		verticalAngle   += mouseSpeed * float( 768/2 - ypos );

		// Direction : Spherical coordinates to Cartesian coordinates conversion
		glm::vec3 direction(
			cos(verticalAngle) * sin(horizontalAngle), 
			sin(verticalAngle),
			cos(verticalAngle) * cos(horizontalAngle)
		);
		
		// Right vector
		glm::vec3 right = glm::vec3(
			sin(horizontalAngle - 3.14f/2.0f), 
			0,
			cos(horizontalAngle - 3.14f/2.0f)
		);
		
		// Up vector
		glm::vec3 up = glm::cross( right, direction );

		// Move forward
		if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
			position += direction * deltaTime * speed;
		}
		// Move backward
		if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
			position -= direction * deltaTime * speed;
		}
		// Strafe right
		if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
			position += right * deltaTime * speed;
		}
		// Strafe left
		if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
			position -= right * deltaTime * speed;
		}
		
		if (glfwGetKey( window, GLFW_KEY_1 ) == GLFW_PRESS){
			blockInd = 0;
		}
		if (glfwGetKey( window, GLFW_KEY_2 ) == GLFW_PRESS){
			blockInd = 1;
		}
		if (glfwGetKey( window, GLFW_KEY_3 ) == GLFW_PRESS){
			blockInd = 2;
		}

		float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

		// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
		ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
		// Camera matrix
		ViewMatrix       = glm::lookAt(
									position,           // Camera is here
									position+direction, // and looks here : at the same position, plus "direction"
									up                  // Head is up (set to 0,-1,0 to look upside-down)
							   );

		// For the next frame, the "last time" will be "now"
		lastTime = currentTime;
	}
	
	
	shape::shape(GLuint vb, GLuint ub, int bs) : vertexBuffer(vb), uvBuffer(ub), bufferSize(bs) { }
	
	shape* getBlock() {return block;}
	
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
		glUniformMatrix4fv(PosID, 1, GL_FALSE, &Pos[0][0]);
	}
	
	void shader::useProgram() {glUseProgram(Shader); }
}
