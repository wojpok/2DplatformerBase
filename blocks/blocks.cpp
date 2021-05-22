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
	// TO DO SOMEDAY IN THE FUTURE: declare each block in seperate file
	//								 and compile into separate module
	GLuint textureAtlas = 0;
	//
	// =================== BASIC BLOCK ==========================
	//
	void block::updateState() {}
	int  block::getState() {return 0;}
	void block::interState() {}
	animator* block::gAnim() {return this->anim;}
	animator* block::anim = new staticAnimator({0, 0});
	//base class, cannot create instance of this block
	block* block::createInstance( ) {return NULL;}
	
	//
	// =================== GRASS BLOCK ==========================
	//
	animator* grass::anim = new staticAnimator({3, 1});
	animator* grass::gAnim() {return this->anim;}
	block* grass::createInstance( ) {return new grass();}
	
	//
	// =================== DIRT BLOCK ==========================
	//
	animator* dirt::anim = new staticAnimator({3, 2});
	animator* dirt::gAnim() {return this->anim;}
	block* dirt::createInstance( ) {return new dirt();}
	//
	// =================== STONE BLOCK ==========================
	//
	UVoffset arr2[4] = {{1, 0}, {1, 1}, {2, 2}, {2, 3}};
	stone::stone() { 
		state = rand() % 10;
		if(state > 3) state = 2;
	}
	int stone::getState() {return state;}
	animator* stone::anim = new multiStableAnimator(arr2, 4);
	animator* stone::gAnim() {return this->anim;}
	block* stone::createInstance( ) {return new stone();}
	
	//
	// =================== LEAF BLOCK ==========================
	//
	animator* leaf::anim = new staticAnimator({1, 2});
	animator* leaf::gAnim() {return this->anim;}
	block* leaf::createInstance( ) {return new leaf();}
	
	//
	// =================== WOOD BLOCK ==========================
	//
	animator* wood::anim = new staticAnimator({3, 3});
	animator* wood::gAnim() {return this->anim;}
	block* wood::createInstance( ) {return new wood();}
	
	//
	// =================== LAMP BLOCK [GAME OF LIFE] ===========
	//
	lamp::lamp() {
		/*state = 0;
		if((con::cX == 7 && con::cY >= 6 && con::cY <= 8)
		|| (con::cY == 6 && con::cX == 6)
		|| (con::cY == 7 && con::cX == 5)) state = 1;*/
		state = 1;
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
	block* lamp::createInstance( ) {return new lamp();}
	
	//
	// =================== BOILER BLOCK ==========================
	//
	UVoffset arr1[10] = {{0, 2}, {0, 1}, {0, 2}, {0, 1}, {0, 1}, {0, 2}, {0, 1}, {0, 3} , {0, 3}, {0, 1}};
	animator* boiler::anim = new synchronusLoopedAnimator(arr1, 10);
	animator* boiler::gAnim() {return this->anim;}
	block* boiler::createInstance( ) {return new boiler();}
	
	

	
	
	
	void initStatics() {
		textureAtlas = view::loadBMP_custom("blocks/atlas2.bmp");
	}
}
