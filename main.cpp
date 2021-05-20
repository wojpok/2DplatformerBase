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


con::chunk *ch;

void mainloop() {
	/*for(int x = 0; x < con::chunk::dimensions; x++) {
			obj::block *b;
			for(int y = 0; y < con::chunk::dimensions; y++) {
				b = ch->getBlock(x, y);
				if(NULL != b) {
					b->interState();
			}
		}
	}*/
	
	ch->updateUVs();
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
	basic->Pos1ID = glGetUniformLocation(basic->Shader, "offset");
	//basic->Pos2ID = glGetUniformLocation(basic->Shader, "offset2");

	glm::mat4 offset = glm::mat4(1);	
	view::refreshFuncSet(mainloop);
	
	ch = new con::chunk();
	
	/*for(int i = 0 ; i < con::chunk::dimensions; i++) {
		for(int f = 0; f < con::chunk::dimensions; f++) {
			//ch->setBlock(f, i, new obj::lamp());
			if(rand()%2 == 0)
				ch->setBlock(f, i, new obj::fan());
			else
				ch->setBlock(f, i, new obj::random());
		}
	}*/
	
	ch->setBlock(1, 1, new obj::block());
	ch->setBlock(2, 2, new obj::grass());
	
	glm::vec3 *off = new glm::vec3[con::chunk::dimensions*con::chunk::dimensions];
	for(int i = 0; i < con::chunk::dimensions*con::chunk::dimensions; i++) {
		off[i] = glm::vec3(0, (i%con::chunk::dimensions)*2, (i/con::chunk::dimensions)*2);
	}
	
	GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, con::chunk::dimensions*con::chunk::dimensions 
				* sizeof(glm::vec3), &off[0], GL_STREAM_DRAW);

	
	
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
		obj::block* b = ch->getBlock(0, 0);
		
		basic->bindPos(ch->ltCorner);
		basic->bindTexture(obj::textureAtlas);
		//basic->bindTexture(b->gAnim()->getTexture(b));
		/*for(int x = 0; x < con::chunk::dimensions; x++) {
			for(int y = 0; y < con::chunk::dimensions; y++) {
				b = ch->getBlock(x, y);
				if(NULL != b) {
					b->gAnim()->stateFunction(b);
					basic->bindTexture(b->gAnim()->getTexture(b));
					basic->bindPos2(*ch->getOffset(x, y));
					
					view::block->draw();
				}
			}
		}*/
		
		
		ch->enableBuffers();
		view::block->drawInstantiated(con::chunk::dimensions*con::chunk::dimensions);
		ch->disableBuffers();
		
		
		view::pushFrame();
	}
	while(view::isContextOpen() );
	
	view::clearContext();
	
	return 0;
}
