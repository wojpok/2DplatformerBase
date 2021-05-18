#ifndef CHUNK_HPP
#define CHUNK_HPP

//class block;

namespace con {
	class chunk {
	public:
		static const int dimensions;
		static glm::mat4** offsets;
		
		chunk();
		
		obj::block** blocks;
		
		glm::mat4 ltCorner;
		
		void setPos(int x, int y);
		
		void setBlock(int x, int y, obj::block* inst);
		obj::block* getBlock(int x, int y);
		obj::block* asyncGetBlock(int x, int y);
		glm::mat4*  getOffset(int x, int y);
	};
	
	extern chunk* curr;
	extern int cX;
	extern int cY;
}

#endif
