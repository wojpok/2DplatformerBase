#include <iostream>
#include <cstdlib>
#include <cstdint>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "view/opengl.hpp"
#include "blocks/blocks.hpp"
#include "blocks/animators.hpp"
#include "controller/chunk.hpp"
#include "controller/player.hpp"

#include "globals.hpp"

con::chunk *ch;

float blockScale = 0.5f;
glm::mat4 scaledMVP;
glm::mat4 MVP;
glm::mat4 centreTransfromation;
// Function called once every second, no need to call this more frequently
void mainloop() {
	ch->intervalState();
}


//Function called on mouse events - in this example it spawns blocks
void mousePress(GLFWwindow* window, int button, int action, int mods) {
	
	/*if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		double xpos = 512 , ypos = 384;
		glfwGetCursorPos(view::window, &xpos, &ypos);
		
		if(xpos >= 141 && xpos <= 800 && ypos <= 755 && ypos >= 97) {
			ch->setBlock(((xpos-141)*8)/((float)(800-141)),
						 8-(((ypos-97)*8)/((float)(755-97))),
						 con::createNewBlock(view::blockInd));
		}
	}*/
}

int main() {
	std::cout<<" Welcome to 2D platformer "<<std::endl;
	
	//setting up everything
	view::createContext();
	obj::initStatics();
	view::shader *basic = new view::shader(); 
	view::frameL = 1;
	
	glfwSetMouseButtonCallback(view::window, mousePress);
	
	basic->Shader = view::LoadShaders("view/basicVertex.glsl","view/basicFragment.glsl");
	basic->TextureID = glGetUniformLocation(basic->Shader, "myTextureSampler");
	basic->MVPID = glGetUniformLocation(basic->Shader, "MVP");
	basic->Pos1ID = glGetUniformLocation(basic->Shader, "offset");

	glm::mat4 offset = glm::mat4(1);
	view::refreshFuncSet(mainloop);
	
	con::chunk::tileMesh = view::block;
	con::chunk::blockShader = basic;
	
	ch = new con::chunk();
	
	//demo map
	int map[64] = {
		1, 0, 0 ,0, 0, 5, 5, 1,
		0, 0, 4 ,5, 0, 5, 1, 2,
		6, 7, 1 ,1, 6, 1, 2, 2,
		7, 2, 2 ,2, 1, 2, 2, 3,
		2, 2, 2 ,2, 2, 2, 3, 3,
		2, 3, 3 ,3, 2, 3, 3, 3,
		0, 0, 4 ,3, 3, 3, 3, 3,
		0, 0, 3 ,3, 3, 3, 3, 3
	};
	
	
	for(int i = 0 ; i < 8; i++) {
		for(int f = 0; f < 8; f++) {
			ch->setBlock(f, i, con::createNewBlock(map[(7 - i)* 8+f]));
			
		}
	}
	
	for(int i = 0 ; i < con::chunk::dimensions; i++) {
		for(int f = 0; f < con::chunk::dimensions; f++) {
			if(i > 16 && f > 16)
				ch->setBlock(f, i, con::createNewBlock(rand()%8));
		}
	}
	
	//player instance
	con::player* ply = new con::player();
	ply->playerShader = new view::shader();
	
	ply->playerShader->Shader = view::LoadShaders("view/playerVertex.glsl","view/playerFragment.glsl");
	ply->playerShader->MVPID = glGetUniformLocation(ply->playerShader->Shader, "MVP");
	ply->playerShader->Pos1ID = glGetUniformLocation(ply->playerShader->Shader, "offset");
	
	ply->playerMesh = view::block;
	
	ply->worldspacePos = glm::mat4(1);
	
	// main loop - draws blocks onto screen and calls computeMatricesFromInputs() 
	// which manages time interval and user inputs
	do { 
		
		ply->update();
		
		view::clearFrame();
		
		view::computeMatricesFromInputs(ply->worldspacePos);
		
		glm::mat4 ProjectionMatrix = view::getProjectionMatrix();
		glm::mat4 ViewMatrix = view::getViewMatrix();
		glm::mat4 ModelMatrix = glm::mat4(1);
		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		scaledMVP = glm::scale(MVP, glm::vec3(blockScale, blockScale, blockScale));
		
		ch->drawAll();
		
		ply->draw(MVP);
		
		view::pushFrame();
	}
	while(view::isContextOpen() );
	
	view::clearContext();
	
	return 0;
}
