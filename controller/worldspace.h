#ifndef WORLDSPACE_H_
#define WORLDSPACE_H_

namespace con {
	
	class chunk;
	
	class worldspace {
	public:
		chunk** chunks;
		static const int dimensionsX = 16;
		static const int dimensionsY = 16;
		
		worldspace();
		~worldspace();
		
		void setChunk(int x, int y, chunk* ch);
		chunk* getChunk(int x, int y);
		
		void drawAll(int x, int y, int xoff, int yoff);
	};
}


#endif
