#include <iostream>
#include <cstdlib>
#include <cstdint>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "../view/opengl.hpp"
#include "../blocks/blocks.hpp"
#include "../blocks/animators.hpp"
#include "chunk.hpp"
#include "player.hpp"

#include "../globals.hpp"

namespace con {
	
	
	void player::update() {
		float speed = 10;
		
		float deltaDist = view::deltaTime * speed;
		
		//int collisionX = ((int)floor(worldspacePos[3][2]));
		//int collisionY = ((int)floor(worldspacePos[3][1]));
		
		// Failed concept of collisions, needs more work
		
		/*#define __desc(x) (((x) == NULL) ? (' ') : ('x'))
		
		for(int y = 2; y > -2; y--) {
			for (int x = -1; x < 3; x++) {
				std::cout<<__desc(ch->getBlock(collisionX + x, collisionY + y));
			}
			std::cout<<std::endl;
		}
		
		std::cout<<collisionX<<" "<<collisionY<<std::endl;*/
		
		
		
		if (glfwGetKey( view::window, GLFW_KEY_UP ) == GLFW_PRESS) {

			/*if(ch->getBlock(collisionX + 1, collisionY) == NULL) {
				worldspacePos[3][1] += deltaDist;
			} else {
				worldspacePos[3][1] = ((collisionX));
			}*/
			worldspacePos[3][1] += deltaDist;
		}	
		else if (glfwGetKey( view::window, GLFW_KEY_DOWN ) == GLFW_PRESS) {
			
			/*if(ch->getBlock(collisionX, collisionY) == NULL) {
				worldspacePos[3][1] -= deltaDist;
			} else {
				worldspacePos[3][1] = ((collisionX+1));
			}*/
			worldspacePos[3][1] -= deltaDist;
		}
		// Strafe right
		if (glfwGetKey( view::window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
			worldspacePos[3][2] += deltaDist;
		}
		// Strafe left
		if (glfwGetKey( view::window, GLFW_KEY_LEFT ) == GLFW_PRESS){
			worldspacePos[3][2] -= deltaDist;
		}
		
		if (glfwGetKey( view::window, GLFW_KEY_SPACE ) == GLFW_PRESS){
			int collisionX = ((int)floor((worldspacePos[3][2] + 0.5f)/blockScale));
			int collisionY = ((int)floor((worldspacePos[3][1] + 0.5f)/blockScale));
			//std::cout<<collisionX<<" "<<collisionY<<std::endl;
			ch->setBlock(collisionX, collisionY, con::createNewBlock( view::blockInd));
		}
	}
	
	
	void player::draw(glm::mat4 MVP) {
		
		worldspacePos[3][0] = -0.001;
		playerShader->useProgram();
		playerShader->bindPos(worldspacePos);
		playerShader->bindMVP(MVP);
		
		GLuint time = glGetUniformLocation(playerShader->Shader, "time");
		glUniform1f(time, glfwGetTime());
		
		playerMesh->draw();
		
		/*std::cout<<worldspacePos[0][0] << worldspacePos[1][0] << worldspacePos[2][0]<< worldspacePos[3][0]<<std::endl;
		std::cout<<worldspacePos[0][1] << worldspacePos[1][1] << worldspacePos[2][1]<< worldspacePos[3][1]<<std::endl;
		std::cout<<worldspacePos[0][2] << worldspacePos[1][2] << worldspacePos[2][2]<< worldspacePos[3][2]<<std::endl;
		std::cout<<worldspacePos[0][3] << worldspacePos[1][3] << worldspacePos[2][3]<< worldspacePos[3][3]<<std::endl;*/
	}

}
