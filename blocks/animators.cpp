#define DEPS
#define VIEW
#define BLOCKS
#define ANIM
#include "../experimentalHeader.h"

namespace obj {
	// Animator with single image
	staticAnimator::staticAnimator(UVoffset t0) {uv = t0;}
	staticAnimator::~staticAnimator(){}
		
	void staticAnimator::stateFunction(block *b) {}
	UVoffset staticAnimator::getTexture(block* b) {return uv; } 
	
	// animator with looped animation (boiler block)
	synchronusLoopedAnimator::synchronusLoopedAnimator(UVoffset* t, int len) {
		l = len;
		uv = t;
	}
	
	synchronusLoopedAnimator::~synchronusLoopedAnimator() {}
		
	void synchronusLoopedAnimator::stateFunction(block *b) {}
	UVoffset synchronusLoopedAnimator::getTexture(block *b) {
		return uv[view::frameCnt%l]; // <- block doesn't implement state-providing function, it works independently
	}
	
	
	//for blocks that needs to change its texture in some unpredictable way (lamps)
	multiStableAnimator::multiStableAnimator(UVoffset* t, int len) 
	{uv = t; l = len; }
	multiStableAnimator::~multiStableAnimator(){};
	
	void multiStableAnimator::stateFunction(block *b) {b->updateState();}
	UVoffset multiStableAnimator::getTexture(block *b) {return uv[b->getState()];}
}
