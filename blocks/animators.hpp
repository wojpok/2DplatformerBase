#ifndef ANIMATORS_HPP
#define ANIMATORS_HPP

namespace obj {
	void initStatics();
	
	extern GLuint textureAtlas;
	
	class block;

	typedef struct {
		uint8_t UVsx;
		uint8_t UVsy;
	} UVoffset;

	class animator {		
	public:
		
		virtual void stateFunction(block* b) = 0;
		virtual UVoffset getTexture(block* b) = 0;
	};
	
	class staticAnimator : public animator {
	public:
		UVoffset uv; 
		staticAnimator(UVoffset off);
		~staticAnimator();
		
		void stateFunction(block *b) override;
		UVoffset getTexture(block* b)  override;
	};
	
	/*class synchronusLoopedAnimator : public animator {
	public:
		GLuint *textures;
		int l;
		synchronusLoopedAnimator(GLuint* t, int len);
		~synchronusLoopedAnimator();
		
		void stateFunction(block *b) override;
		GLuint getTexture(block *b) override;
	};
	
	class asynchronousStateAnimator : public animator {
	public:
		GLuint *textures;
		int l;
		asynchronousStateAnimator(GLuint* t, int len);
		~asynchronousStateAnimator();
		
		void stateFunction(block *b) override;
		GLuint getTexture(block *b) override;
	};*/
}

#endif
