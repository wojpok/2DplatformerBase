#ifndef ANIMATORS_HPP
#define ANIMATORS_HPP

namespace obj {
	void initStatics();
	
	class block;

	class animator {		
	public:
		GLuint texture; 
		virtual void stateFunction(block* b) = 0;
		virtual GLuint getTexture(block* b) = 0;
	};
	
	class staticAnimator : public animator {
	public:

		staticAnimator(GLuint t0);
		~staticAnimator();
		
		void stateFunction(block *b) override;
		GLuint getTexture(block* b)  override;
	};
	
	class synchronusLoopedAnimator : public animator {
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
	};
}

#endif
