#include <iostream>
#include <cstdint>
#include <cstdlib>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "../view/opengl.hpp"
#include "blocks.hpp"
#include "animators.hpp"
#include "../controller/chunk.hpp"

namespace obj {
	GLuint textureAtlas = 0;
	
	void block::updateState() {}
	int  block::getState() {return 0;}
	void block::interState() {}
	animator* block::gAnim() {return this->anim;}
	
	animator* block::anim = new staticAnimator({1, 1});
	
	animator* grass::anim = new staticAnimator({3, 1});
	animator* grass::gAnim() {return this->anim;}
	
	animator* dirt::anim = new staticAnimator({3, 2});
	animator* dirt::gAnim() {return this->anim;}
	
	animator* leaf::anim = new staticAnimator({1, 2});
	animator* leaf::gAnim() {return this->anim;}
	UVoffset arr1[4] = {{1, 0}, {1, 1}, {2, 2}, {2, 3}};
	animator* water_surface::anim = new synchronusLoopedAnimator(arr1, 3);
	animator* water_surface::gAnim() {return this->anim;}
	
	UVoffset arr2[4] = {{1, 0}, {1, 1}, {2, 2}, {2, 3}};
	
	stone::stone() { 
		state = rand() % 10;
		if(state > 3) state = 2;
	}
	int stone::getState() {return state;}
	animator* stone::anim = new multiStableAnimator(arr2, 4);
	animator* stone::gAnim() {return this->anim;}
	
	lamp::lamp() {
		state = 0;
		/*if((con::cX == 7 && con::cY >= 6 && con::cY <= 8)
		|| (con::cY == 6 && con::cX == 6)
		|| (con::cY == 7 && con::cX == 5)) state = 1;*/
		state = rand() % 2;
	}
	int lamp::getState() {return (state & 1);}
	void lamp::updateState() {}
	void lamp::interState() {
		if(view::frameCnt%2 == 0) {
			int n = 0;
			for(int i = -1; i < 2; i++) {
				for(int j = -1; j < 2; j++) {
						block* neigh = con::curr->asyncGetBlock(con::cX+i, con::cY+j);
						if(neigh != NULL)
							n += (neigh->getState()&1);
				}
			}
			state = ((((state == 0) ? (n == 3) : (n >= 3 && n <= 4))<<1) | state) ;
		}
		else {
			state = (state >> 1);
		}
	}
	animator* lamp::gAnim() {return anim;}
	UVoffset arr3[2] = {{2, 0}, {2, 1}};
	animator* lamp::anim = new multiStableAnimator(arr3,2);
	
	void initStatics() {
		textureAtlas = view::loadBMP_custom("blocks/atlas.bmp");
	}
}
