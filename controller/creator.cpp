#define DEPS
#define BLOCKS
#include "../experimentalHeader.h"

namespace con {
	
	//constructor pointers - very helpful approach when addresing blocks with ids
	obj::block* (*constructorList[])() = {
		obj::block::createInstance,
		obj::grass::createInstance,
		obj::dirt::createInstance,
		obj::stone::createInstance,
		obj::leaf::createInstance, 
		obj::wood::createInstance, //5
		obj::lamp::createInstance,
		obj::boiler::createInstance,  //boiler maker /s
		obj::planking::createInstance,
		obj::bricks::createInstance
	}; 
	
	obj::block* createNewBlock(int id) {
		return constructorList[id]();
	}
	
}
