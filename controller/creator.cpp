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
	
	//wskaźniki na funkcje
	obj::block* (*constructorList[])() = {
		obj::block::createInstance,
		obj::grass::createInstance,
		obj::dirt::createInstance,
		obj::stone::createInstance,
		obj::water_surface::createInstance,
		obj::leaf::createInstance,//5
		obj::lamp::createInstance	
	}; 
	
	obj::block* createNewBlock(int id) {
		return constructorList[id]();
	}
	
}
