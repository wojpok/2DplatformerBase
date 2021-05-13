#ifndef ANIMATORS_HPP
#define ANIMATORS_HPP

namespace obj {
	class block;

	class animator {
	public: 
		virtual void stateFunction(block* b) = 0;
		virtual GLuint getTexture(block* b) = 0;
	};
	
	class staticAnimator : public animator {
	public:
		GLuint texture;
		staticAnimator(GLuint t0);
		~staticAnimator();
		
		void stateFunction(block *b);
		GLuint getTexture(block* b);
	};
	
}

#endif
