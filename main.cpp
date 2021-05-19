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
	for(int x = 0; x < con::chunk::dimensions; x++) {
			obj::block *b;
			for(int y = 0; y < con::chunk::dimensions; y++) {
				b = ch->getBlock(x, y);
				if(NULL != b) {
					b->interState();
			}
		}
	}
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
	
	/*GLuint grass = view::loadBMP_custom("blocks/simplegrass.bmp");
	GLuint stone = view::loadBMP_custom("blocks/simplestone.bmp");*/
	glm::mat4 offset = glm::mat4(1);	
	view::refreshFuncSet(mainloop);
	
	ch = new con::chunk();
	
	for(int i = 0 ; i < con::chunk::dimensions; i++) {
		for(int f = 0; f < con::chunk::dimensions; f++) {
			//ch->setBlock(f, i, new obj::lamp());
			if(rand()%2 == 0)
				ch->setBlock(f, i, new obj::fan());
			else
				ch->setBlock(f, i, new obj::random());
		}
	}
	
	/*glm::mat4 offsets[ con::chunk::dimensions*con::chunk::dimensions];
	for(int i = 0; i <  con::chunk::dimensions*con::chunk::dimensions; i++) 
		offsets[i] = ch->getOffset(i % con::chunk::dimensions, i / con::chunk::dimensions);
	*/
	glm::vec3 *off = new glm::vec3[con::chunk::dimensions*con::chunk::dimensions];
	for(int i = 0; i < con::chunk::dimensions*con::chunk::dimensions; i++) {
		off[i] = glm::vec3(0, (i%con::chunk::dimensions)*2, (i/con::chunk::dimensions)*2);
	}
	
	GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, con::chunk::dimensions*con::chunk::dimensions 
				* sizeof(glm::vec3), &off[0], GL_STREAM_DRAW);

	
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

	//glBindVertexArray(0);
	
	
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
		basic->bindTexture(b->gAnim()->getTexture(b));
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
		
		//view::block->draw();
		/*glEnableVertexAttribArray(0);
		 glBindVertexArray(view::block->vertexBuffer);
         glDrawElementsInstanced(GL_TRIANGLES, 
			view::block->bufferSize, GL_UNSIGNED_INT, 0,  
			con::chunk::dimensions*con::chunk::dimensions );
         glBindVertexArray(0);*/
		
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, view::block->vertexBuffer);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);
		
		// 2nd attribute buffer : positions of particles' centers
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, view::block->uvBuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			2,                                // size : x + y + z + size => 4
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// 3rd attribute buffer : particles' colors
		glEnableVertexAttribArray(3);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glVertexAttribPointer(
			3,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size : r + g + b + a => 4
			GL_FLOAT,                 // type
			GL_FALSE,                          // normalized?    *** YES, this means that the unsigned char[4] will be accessible with a vec4 (floats) in the shader ***
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// These functions are specific to glDrawArrays*Instanced*.
		// The first parameter is the attribute buffer we're talking about.
		// The second parameter is the "rate at which generic vertex attributes advance when rendering multiple instances"
		// http://www.opengl.org/sdk/docs/man/xhtml/glVertexAttribDivisor.xml
		glVertexAttribDivisor(0, 0); // particles vertices : always reuse the same 4 vertices -> 0
		glVertexAttribDivisor(1, 0); // positions : one per quad (its center)                 -> 1
		glVertexAttribDivisor(3, 1); // color : one per quad                                  -> 1

		// Draw the particules !
		// This draws many times a small triangle_strip (which looks like a quad).
		// This is equivalent to :
		// for(i in ParticlesCount) : glDrawArrays(GL_TRIANGLE_STRIP, 0, 4), 
		// but faster.
		glDrawArraysInstanced(GL_TRIANGLES, 0, view::block->bufferSize, con::chunk::dimensions*con::chunk::dimensions);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(3);

		
		
		view::pushFrame();
	}
	while(view::isContextOpen() );
	
	view::clearContext();
	
	return 0;
}
