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
	animator* block::gAnim() {return this->anim;}
	
	animator* block::anim = new staticAnimator(0);
	
	
	lamp::lamp() {time = 0; state = 0;}
	float lamp::getTime() {return time;}
	int   lamp::getState() {return state;}
	void  lamp::setState(int s) {state = s;} 
	
	GLuint *t = new GLuint[2];
		
	animator* stone::anim = new synchronusLoopedAnimator(t,2);
	animator* stone::gAnim() {return this->anim;}
	
	void initStatics() {
		
		
		t[0] = view::loadBMP_custom("blocks/simpledirt.bmp");
		t[1] = view::loadBMP_custom("blocks/simplestone.bmp");
		
		block::anim->texture = view::loadBMP_custom("blocks/simplegrass.bmp");
	}
}
