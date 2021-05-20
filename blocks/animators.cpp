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
	staticAnimator::staticAnimator(UVoffset t0) {uv = t0;}
	staticAnimator::~staticAnimator(){}
		
	void staticAnimator::stateFunction(block *b) {}
	UVoffset staticAnimator::getTexture(block* b) {return uv; }
	
	
	synchronusLoopedAnimator::synchronusLoopedAnimator(UVoffset* t, int len) {
		l = len;
		uv = t;
	}
	
	synchronusLoopedAnimator::~synchronusLoopedAnimator() {}
		
	void synchronusLoopedAnimator::stateFunction(block *b) {}
	UVoffset synchronusLoopedAnimator::getTexture(block *b) {
		return uv[view::frameCnt%l];
	}
	
	
	multiStableAnimator::multiStableAnimator(UVoffset* t, int len) 
	{uv = t; l = len; }
	multiStableAnimator::~multiStableAnimator(){};
	
	void multiStableAnimator::stateFunction(block *b) {b->updateState();}
	UVoffset multiStableAnimator::getTexture(block *b) {return uv[b->getState()];}
}
