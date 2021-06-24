#ifndef experimentalHeader
#define experimantalHeader

// changing macros require project rebuilding
#if 0
	#define NO_CAM_MOVEMENT
#endif

#define CHUNK_SIZE 4
#define CHUNK_LOG_SIZE 2
#define __chunkIndexer(x, y) ((y<<CHUNK_LOG_SIZE)|x)

#ifdef DEPS
	#include <iostream>
	#include <cstdlib>
	#include <cstdint>

	#include <GL/glew.h>
	#include <GLFW/glfw3.h>
	#include <glm/glm.hpp>
	#include <glm/gtc/matrix_transform.hpp>
	#include <glm/gtx/transform.hpp>
#endif

#ifdef VIEW
	namespace view {
		extern GLFWwindow* window;
		extern float deltaTime;
		extern float frameL;
		extern int frameCnt;
		extern int blockInd;
		
	}
	#include "view/opengl.hpp" 
	
	//global instance of only block needed right now
	namespace view {
		extern shape* block;
	}
	
#endif

#ifdef BLOCKS
	#include "blocks/blocks.hpp"
#endif

#ifdef ANIM
	#include "blocks/animators.hpp"

	namespace obj {
		extern GLuint textureAtlas;
	}
#endif

#ifdef CHUNK
	#include "controller/chunk.hpp"

	namespace con {
		extern chunk* curr;
		extern int cX;
		extern int cY;
	}

	extern con::chunk *ch;
#endif


#ifdef WORLD
	#include "controller/worldspace.h"
	
	extern con::worldspace *world;
#endif

#ifdef PLAYER
	#include "controller/player.hpp"
#endif

	extern float blockScale;

	extern glm::mat4 MVP;
	extern glm::mat4 scaledMVP;

	extern glm::mat4 centreTransfromation;

	extern int windowHeight;
	extern int windowWidth;


#endif
