#include <iostream>
#include <cstdint>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "../view/opengl.hpp"
#include "blocks.hpp"
#include "animators.hpp"

namespace obj {
	float block::getTime() {return 0;}
	int   block::getState() {return 0;}
	void  block::setState(int s) {}
	
	const animator* block::anim = new staticAnimator(0);
	
	const animator* stone::anim = new staticAnimator(0);
	
	
	lamp::lamp() {time = 0; state = 0;}
	float lamp::getTime() {return time;}
	int   lamp::getState() {return state;}
	void  lamp::setState(int s) {state = s;} 
}
