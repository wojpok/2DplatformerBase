#include <iostream>
#include <cstdint>
#include <cstring>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

//#include "view/opengl.hpp"
//#include "view/shaders.hpp"
#include "../blocks/blocks.hpp"
#include "../blocks/animators.hpp"

#include "chunk.hpp"

namespace con {
	
	 const int chunk::dimensions = 128;
	
	chunk* curr = NULL;
	int cX = 0;
	int cY = 0;
	
	glm::vec3* chunk::offsets = NULL;
	GLuint chunk::offsetBuffer = 0;
	
	chunk::chunk() {
		if(offsets == NULL) {
			offsets = new glm::vec3[dimensions*dimensions];
			for(int y = 0; y < dimensions; y++) {
				for(int x = 0 ; x < dimensions; x++) {
					offsets[y*dimensions+x] = glm::vec3(0, 2*y, 2*x);
				}
			}
			
			glGenBuffers(1, &offsetBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, offsetBuffer);
			glBufferData(GL_ARRAY_BUFFER, dimensions*dimensions 
				* sizeof(glm::vec3), &offsets[0], GL_STREAM_DRAW);
		}
		
		atlasUVs = (uint8_t*) calloc(sizeof(uint8_t), dimensions*dimensions*2);
		
		
		
		glGenBuffers(1, &UVsBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, UVsBuffer);
		glBufferData(GL_ARRAY_BUFFER, dimensions*dimensions*2 
			* sizeof(uint8_t), &atlasUVs[0], GL_STREAM_DRAW);
		
		atlasUVs[0] =  1;
		
		blocks = (obj::block**)calloc(sizeof(obj::block*),dimensions*dimensions);
		for(int i = 0; i < dimensions*dimensions; i++)
			blocks[i] = NULL;
		ltCorner = glm::mat4(1);
	}
	
	void chunk::enableBuffers() {
		glEnableVertexAttribArray(3);
		glBindBuffer(GL_ARRAY_BUFFER, offsetBuffer);
		glVertexAttribPointer(
			3,                               
			3,                                
			GL_FLOAT,                 // type
			GL_FALSE,                          // normalized?    *** YES, this means that the unsigned char[4] will be accessible with a vec4 (floats) in the shader ***
			0,                                // stride
			(void*)0                          // array buffer offset
		);
		
		glVertexAttribDivisor(3, 1); // color : one per quad
		
		
		
		glEnableVertexAttribArray(4);
		glBindBuffer(GL_ARRAY_BUFFER, UVsBuffer);
		glVertexAttribPointer(
			4,                               
			2,                                
			GL_UNSIGNED_BYTE,                 // type
			GL_FALSE,                          // normalized?    *** YES, this means that the unsigned char[4] will be accessible with a vec4 (floats) in the shader ***
			0,                                // stride
			(void*)0                          // array buffer offset
		);
		
		glVertexAttribDivisor(4, 1); // color : one per quad        
	}
	
	void chunk::disableBuffers() {
		glDisableVertexAttribArray(3);
		glDisableVertexAttribArray(4);
	}
	
	void chunk::updateUVs() {
		obj::block* c;
		int cord;
		for(int y = 0 ; y < dimensions; y++) {
			for(int x = 0; x < dimensions; x++) {
				cord = y*dimensions+x;
				if((c = blocks[cord]) != NULL ) {
					
					obj::UVoffset off = c->gAnim()->getTexture(c);
					atlasUVs[cord*2 ] = off.UVsx;
					atlasUVs[cord*2 +1] = off.UVsy;
				}	
			}
		}
		
		glBindBuffer(GL_ARRAY_BUFFER, UVsBuffer);
		glBufferData(GL_ARRAY_BUFFER, dimensions*dimensions*2 
			* sizeof(uint8_t), &atlasUVs[0], GL_STREAM_DRAW);
	}
	
	void chunk::setBlock(int x, int y, obj::block* inst) {
		if(blocks[y*dimensions+x] != NULL) delete blocks[y*dimensions+x];
		curr = this;
		cX = x;
		cY = y;
		blocks[y*dimensions+x] = inst;
	}
	
	obj::block* chunk::getBlock(int x, int y) {
		curr = this;
		cX = x;
		cY = y;
		return blocks[(y)*dimensions +(x)];
	}
	
	obj::block* chunk::asyncGetBlock(int x, int y) {
		if(x < 0 || y < 0 || x >= dimensions || y >= dimensions) return NULL;
		return blocks[(y)*dimensions +(x)];
	}
	
	
	void chunk::setPos(int x, int y) {
		ltCorner[3][2] = x;
		ltCorner[3][1] = y;
	}
	
	/*glm::mat4* chunk::getOffset(int x, int y) {
		return offsets[y*dimensions +x];
	}*/

}
