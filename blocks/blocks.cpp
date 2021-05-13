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
	void block::updateState() {}
	int   block::getState() {return 0;}
	animator* block::gAnim() {return this->anim;}
	
	animator* block::anim = new staticAnimator(0);
	
	GLuint *t2 = new GLuint[3];
	
	random::random() {state = rand()%3;}
	int random::getState() {return state;}
	void random::updateState() {}
	animator* random::gAnim() {return anim;}
	animator* random::anim = new asynchronousStateAnimator(t2,3);
	
	GLuint *t3 = new GLuint[3];
	
	lamp::lamp() {
		time = 0; state = 0;
		if((con::cX == 7 && con::cY >= 6 && con::cY <= 8)
		|| (con::cY == 6 && con::cX == 6)
		|| (con::cY == 7 && con::cX == 5)) state = 1;
	}
	int lamp::getState() {return (state & 1);}
	void lamp::updateState() {
		time += view::deltaTime;
		if(time > 0.5) {
			time -= 0.5;	
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
	}
	animator* lamp::gAnim() {return anim;}
	animator* lamp::anim = new asynchronousStateAnimator(t3,2);
	
	
	
	GLuint *t = new GLuint[4];
		
	animator* fan::anim = new synchronusLoopedAnimator(t,4);
	animator* fan::gAnim() {return this->anim;}
	
	void initStatics() {
		
		t3[0] = view::loadBMP_custom("blocks/lampoff.bmp");
		t3[1] = view::loadBMP_custom("blocks/lampon.bmp");
		
		t2[0] = view::loadBMP_custom("blocks/randstate1.bmp");
		t2[1] = view::loadBMP_custom("blocks/randstate2.bmp");
		t2[2] = view::loadBMP_custom("blocks/randstate3.bmp");
		
		t[0] = view::loadBMP_custom("blocks/radar1.bmp");
		t[1] = view::loadBMP_custom("blocks/radar2.bmp");
		t[2] = view::loadBMP_custom("blocks/radar4.bmp");
		t[3] = view::loadBMP_custom("blocks/radar3.bmp");
		
		block::anim->texture = view::loadBMP_custom("blocks/simplegrass.bmp");
	}
}
