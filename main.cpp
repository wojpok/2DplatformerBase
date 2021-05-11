#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "view/opengl.hpp"
#include "blocks/blocks.hpp"



int main() {
	std::cout<<" Welcome to 2D platformer "<<std::endl;
	
	view::createContext();
	
	do { 
		view::clearFrame();
		view::pushFrame();
	}
	while(view::isContextOpen() );
	
	view::clearContext();
	
	return 0;
}
