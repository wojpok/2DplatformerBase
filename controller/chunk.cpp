#define DEPS
#define VIEW
#define BLOCKS
#define CHUNK
#define ANIM
#define PLAYER
#include "../experimentalHeader.h"


namespace con {
	
	const int chunk::dimensions = CHUNK_SIZE;
	
	view::shape * chunk::tileMesh = NULL;
	view::shader * chunk::blockShader = NULL;
	
	chunk* curr = NULL;
	int cX = 0;
	int cY = 0;
	
	glm::vec3* chunk::offsets = NULL;
	GLuint chunk::offsetBuffer = 0;
	
	
	// constructor - calculates offsets from chunk location for eash block
	chunk::chunk() {
		if(offsets == NULL) {
			offsets = new glm::vec3[dimensions*dimensions];
			for(int y = 0; y < dimensions; y++) {
				for(int x = 0 ; x < dimensions; x++) {
					offsets[y*dimensions+x] = glm::vec3(0, y, x);
				}
			}
			
			glGenBuffers(1, &offsetBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, offsetBuffer);
			glBufferData(GL_ARRAY_BUFFER, dimensions*dimensions 
				* sizeof(glm::vec3), &offsets[0], GL_STREAM_DRAW);
		}
		
		atlasUVs = (uint8_t*) calloc(sizeof(uint8_t), dimensions*dimensions*2);
		
		
		// Creating buffer for unique UVS of each block
		glGenBuffers(1, &UVsBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, UVsBuffer);
		glBufferData(GL_ARRAY_BUFFER, dimensions*dimensions*2 
			* sizeof(uint8_t), &atlasUVs[0], GL_STREAM_DRAW);
		
		//atlasUVs[0] =  1;
		
		blocks = (obj::block**)calloc(sizeof(obj::block*),dimensions*dimensions);
		for(int i = 0; i < dimensions*dimensions; i++)
			blocks[i] = NULL;
		ltCorner = glm::mat4(1);
	}
	
	//buffer providing functions
	void chunk::enableBuffers() {
		blockShader->useProgram();	
		blockShader->bindMVP(scaledMVP);
		
		blockShader->bindTexture(obj::textureAtlas);
		
		GLuint time = glGetUniformLocation(blockShader->Shader, "time");
		glUniform1f(time, glfwGetTime());
		
		
		glEnableVertexAttribArray(3);
		glBindBuffer(GL_ARRAY_BUFFER, offsetBuffer);
		glVertexAttribPointer(
			3,                               
			3,                                
			GL_FLOAT,                 // type
			GL_FALSE,                          // normalized?    *** YES, this means that the unsigned char[4] will be accessible with a vec4 (floats) in the shader ***
			0,                                // stride
			(void*)0                          // array buffer offset
		);
		
		glVertexAttribDivisor(3, 1); 
		
	}
	
	void chunk::drawAll() {
		blockShader->bindPos(ltCorner);
		
		dynamicState();
		updateUVs();
		
			
		
		glEnableVertexAttribArray(4);
		glBindBuffer(GL_ARRAY_BUFFER, UVsBuffer);
		glVertexAttribPointer(
			4,                               
			2,                                
			GL_UNSIGNED_BYTE,                 // type
			GL_FALSE,                          
			0,                                // stride
			(void*)0                          // array buffer offset
		);
		
		glVertexAttribDivisor(4, 1);    
		
		//enableBuffers();
		tileMesh->drawInstantiated(dimensions*dimensions);
		//disableBuffers();
		
		glDisableVertexAttribArray(4);
	}
	
	
	void chunk::disableBuffers() {
		glDisableVertexAttribArray(3);
		
	}
	
	//iterating through all blocks and collecting needed uvs
	void chunk::updateUVs() {
		obj::block* c;
		int cord;
		for(int y = 0 ; y < dimensions; y++) {
			for(int x = 0; x < dimensions; x++) {
				cord = y*dimensions+x;
				if((c = blocks[cord]) != NULL ) {
					
					obj::UVoffset off = c->gAnim()->getTexture(c);
					atlasUVs[(cord<<1) ] = off.UVsx;
					atlasUVs[(cord<<1)|1] = off.UVsy;
				}	
			}
		}
		
		glBindBuffer(GL_ARRAY_BUFFER, UVsBuffer);
		glBufferData(GL_ARRAY_BUFFER, dimensions*dimensions*2 
			* sizeof(uint8_t), &atlasUVs[0], GL_STREAM_DRAW);
	}
	
	void chunk::intervalState() {
		obj::block *b;
		
		for(int x = 0; x < dimensions; x++) {
			//updates every block's state with interval function;
			for(int y = 0; y < dimensions; y++) {
				b = getBlock(x, y);
				if(NULL != b) {
					b->interState(); 
				}
			}
		}
	}
	
	void chunk::dynamicState() {
		obj::block *b;
		
		for(int x = 0; x < dimensions; x++) {
			//updates every block's state with interval function;
			for(int y = 0; y < dimensions; y++) {
				b = getBlock(x, y);
				if(NULL != b) {
					b->updateState(); 
				}
			}
		}
	}
	
	void chunk::setBlock(int x, int y, obj::block* inst) {
		// when inst == NULL basically is setBlock == removeBlock
		if(x >= 0 && x < dimensions && y >= 0 && y < dimensions) {
			int cord = __chunkIndexer(x, y);
			if(blocks[cord] != NULL) {
				delete blocks[cord];
				atlasUVs[cord*2 ] = 0;
				atlasUVs[cord*2 +1] = 0;
			}
			curr = this;
			cX = x;
			cY = y;
			blocks[cord] = inst;
		}
	}
	
	obj::block* chunk::getBlock(int x, int y) {
		if(x >= 0 && x < dimensions && y >= 0 && y < dimensions) {
			curr = this;
			cX = x;
			cY = y;
			return blocks[__chunkIndexer(x, y)];
		}
		
		return NULL;
	}
	
	obj::block* chunk::asyncGetBlock(int x, int y) {
		if(x < 0 || y < 0 || x >= dimensions || y >= dimensions) return NULL;
		return blocks[__chunkIndexer(x, y)];
	}
	
	
	void chunk::setPos(int x, int y) {
		ltCorner[3][2] = x;
		ltCorner[3][1] = y;
	}
}
