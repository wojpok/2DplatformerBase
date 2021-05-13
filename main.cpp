#include <iostream>
#include <cstdlib>
#include <cstdint>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "view/opengl.hpp"
//#include "view/shaders.hpp"
#include "blocks/blocks.hpp"
#include "blocks/animators.hpp"
#include "controller/chunk.hpp"


void mainloop() {
	//std::cout<<view::frameCnt<<std::endl;
}

int main() {
	std::cout<<" Welcome to 2D platformer "<<std::endl;
	
	view::createContext();
	
	obj::initStatics();
	
	view::shader sh;

	view::shader *basic = &sh; 
	
	view::frameL = 0.5;
	
	basic->Shader = view::LoadShaders("view/basicVertex.glsl","view/basicFragment.glsl");
	basic->TextureID = glGetUniformLocation(basic->Shader, "myTextureSampler");
	basic->MVPID = glGetUniformLocation(basic->Shader, "MVP");
	basic->PosID = glGetUniformLocation(basic->Shader, "offset");
	
	/*GLuint grass = view::loadBMP_custom("blocks/simplegrass.bmp");
	GLuint stone = view::loadBMP_custom("blocks/simplestone.bmp");*/
	glm::mat4 offset = glm::mat4(1);	
	view::refreshFuncSet(mainloop);
	
	con::chunk ch;
	for(int i = 0 ; i < 16; i++) {
		for(int f = 0; f < 16; f++) {
			ch.setBlock(f, i, new obj::lamp());
		}
	}
	
	/*for(int i = 0 ; i < 8; i++) {
		for(int f = 8; f < 16; f++) {
			ch.setBlock(f, i, new obj::fan());
		}
	}
	
	for(int i = 8 ; i < 16; i++) {
		for(int f = 0; f < 8; f++) {
			ch.setBlock(f, i, new obj::random());
		}
	}*/
	
	do { 
		view::clearFrame();
		
		view::computeMatricesFromInputs();
		
		glm::mat4 ProjectionMatrix = view::getProjectionMatrix();
		glm::mat4 ViewMatrix = view::getViewMatrix();
		glm::mat4 ModelMatrix = glm::mat4(1);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		MVP = glm::scale(MVP, glm::vec3(0.125f, 0.125f, 0.125f));
		
		basic->useProgram();	
		basic->bindMVP(MVP);
		

		//offset[3][2] += view::deltaTime;
		//offset[3][1] += view::deltaTime;
		obj::block* b;
		
		for(int x = 0; x < 16; x++) {
			for(int y = 0; y < 16; y++) {
				b = ch.getBlock(x, y);
				if(NULL != b) {
					b->gAnim()->stateFunction(b);
					basic->bindTexture(b->gAnim()->getTexture(b));
					offset = ch.ltCorner * *ch.getOffset(x, y);
					basic->bindPos(offset);
					view::block->draw();
				}
			}
		}
		
		view::pushFrame();
	}
	while(view::isContextOpen() );
	
	view::clearContext();
	
	return 0;
}
