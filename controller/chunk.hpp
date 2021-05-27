#ifndef CHUNK_HPP
#define CHUNK_HPP

/*
 * 			Chunks are responsible for managing active blocks and providing data for instanciated draw.		
 * 
 */
 
 
namespace con {
	
	obj::block* createNewBlock(int id);
	
	class chunk {
	public:
		static const int dimensions;
		static glm::vec3* offsets;
		static GLuint offsetBuffer;
		
		static view::shape *tileMesh;
		static view::shader *blockShader;
		
		uint8_t *atlasUVs;
		GLuint UVsBuffer;
		
		chunk();
		
		obj::block** blocks;
		
		glm::mat4 ltCorner;
		
		void updateUVs();
		void intervalState();
		void dynamicState();
		
		//move chunk
		void setPos(int x, int y);
		void setBlock(int x, int y, obj::block* inst);
		
		// getBlock not only return needed block, but also saves last used chunk in 
		// global variables declared below class defininition. Ugly solution but necesarry for more complex blocks (lamps)
		
		obj::block* getBlock(int x, int y);
		
		//slight difference than normal get block, it doesn't save last used chunk
		obj::block* asyncGetBlock(int x, int y);
		
		//instanced draw
		void enableBuffers();
		void disableBuffers();
	};
	
	extern chunk* curr;
	extern int cX;
	extern int cY;
}

#endif
