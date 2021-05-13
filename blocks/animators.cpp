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
	staticAnimator::staticAnimator(GLuint t0) {texture = t0;}
	staticAnimator::~staticAnimator(){}
		
	void staticAnimator::stateFunction(block *b) {}
	GLuint staticAnimator::getTexture(block* b) {return texture; }
	
	
	synchronusLoopedAnimator::synchronusLoopedAnimator(GLuint* t, int len) {
		l = len;
		textures = t;
	}
	
	synchronusLoopedAnimator::~synchronusLoopedAnimator() {}
		
	void synchronusLoopedAnimator::stateFunction(block *b) {}
	GLuint synchronusLoopedAnimator::getTexture(block *b) {
		return textures[view::frameCnt%l];
	}
	
	
	asynchronousStateAnimator::asynchronousStateAnimator(GLuint* t, int len) 
	{textures = t; l = len; }
	asynchronousStateAnimator::~asynchronousStateAnimator(){};
	
	void asynchronousStateAnimator::stateFunction(block *b) {b->updateState();}
	GLuint asynchronousStateAnimator::getTexture(block *b) {return textures[b->getState()];}
}
