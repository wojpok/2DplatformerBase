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
//#include "blocks/animators.hpp"

#include "chunk.hpp"

namespace con {
	
	chunk* curr = NULL;
	int cX = 0;
	int cY = 0;
	
	glm::mat4** chunk::offsets = NULL;
	
	chunk::chunk() {
		if(offsets == NULL) {
			offsets = new glm::mat4*[256];
			for(int y = 0; y < 16; y++) {
				for(int x = 0 ; x < 16; x++) {
					glm::mat4* id = new glm::mat4(1);
					(*id)[3][2] = 2*x; (*id)[3][1] = 2*y;
					
					//offsets[y*dimensions+x] = id;
					offsets[y*16+x] = id;
				}
			}
		}
		
		blocks = (obj::block**)calloc(sizeof(obj::block*),256);
		for(int i = 0; i < 256; i++)
			blocks[i] = NULL;
		ltCorner = glm::mat4(1);
	}
	
	void chunk::setBlock(int x, int y, obj::block* inst) {
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
		if(x < 0 || y < 0 || x > 15 || y > 15) return NULL;
		return blocks[(y)*dimensions +(x)];
	}
	
	
	void chunk::setPos(int x, int y) {
		ltCorner[3][2] = x;
		ltCorner[3][1] = y;
	}
	
	glm::mat4* chunk::getOffset(int x, int y) {
		return offsets[y*dimensions +x];
	}

}
