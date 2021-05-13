#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>


#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "opengl.hpp"

namespace view {
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
	
	
	int frameCnt = 1;
	float timeElapsed = 0;
	float frameL = 1;
	
	void (*refreshFunc)();
	
	void refreshFuncSet(void (*ptr)()) {
		refreshFunc = ptr;
	}
	
	void computeMatricesFromInputs(){

		// glfwGetTime is called only once, the first time this function is called
		static double lastTime = glfwGetTime();

		// Compute time difference between current and last frame
		double currentTime = glfwGetTime();
		deltaTime = float(currentTime - lastTime);

		if((timeElapsed += deltaTime) > frameL) {
			frameCnt++;
			timeElapsed -= frameL;
			refreshFunc();
		}

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
}
