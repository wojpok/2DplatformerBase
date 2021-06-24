#define DEPS
#define VIEW
#define BLOCKS
#define WORLD
#define CHUNK
#define ANIM
//#define PLAYER
#include "../experimentalHeader.h"

namespace con {
	
	#define __wsIndexer(x, y) (((y)*dimensionsY)+(x))
		
	worldspace::worldspace() : chunks(new chunk*[dimensionsX*dimensionsY]) {}
	worldspace::~worldspace() {
		/*for(int i = 0; i < dimensionsX*dimensionsY; i++)
			if(chunks[i] != NULL) delete chunks[i];
	
		delete [] chunks;*/
	}
	
	void worldspace::setChunk(int x, int y, chunk* ch) {
		if(ch != NULL) {ch->setPos((x<<CHUNK_LOG_SIZE), (y<<CHUNK_LOG_SIZE));}
		
		if(x >= 0 && x < dimensionsX && y >= 0 && y< dimensionsY)
			chunks[__wsIndexer(x, y)] = ch;
	}
	
	chunk* worldspace::getChunk(int x, int y) {
		if(x >= 0 && x < dimensionsX && y >= 0 && y< dimensionsY)
			return chunks[__wsIndexer(x, y)];
		return NULL;
	}
	
	void worldspace::drawAll(int x, int y, int xoff, int yoff) {
		chunk::enableBuffers();
		
		for(int i = x; i < x + xoff; i++)
			for(int j = y; j < y + yoff; j++)
				if(i >= 0 && i < dimensionsX && j >= 0 && j< dimensionsY && chunks[__wsIndexer(i, j)] != NULL) {
					
					chunks[__wsIndexer(i, j)]->drawAll();
					
				}
		chunk::disableBuffers();
	}
}


