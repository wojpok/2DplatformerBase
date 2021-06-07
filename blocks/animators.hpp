#ifndef ANIMATORS_HPP
#define ANIMATORS_HPP

/*
 * 			Animators are very specific objects
 * 			They serve as database with UVs for specific blocks
 * 
 * 			Reason thy their functionality isn't merged into blocks is because
 *  		In the future different blocks will have different behaviours and
 * 			separating them avoids copying and pasting tons of code.
 */

namespace obj {
	void initStatics();
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
	private:
		UVoffset uv; 
	public:
		staticAnimator(UVoffset off);
		~staticAnimator();
		
		void stateFunction(block *b) override;
		UVoffset getTexture(block* b)  override;
	};
	
	class synchronusLoopedAnimator : public animator {
	private:
		UVoffset* uv; 
		int l;
	public:
		synchronusLoopedAnimator(UVoffset* t, int len);
		~synchronusLoopedAnimator();
		
		void stateFunction(block *b) override;
		UVoffset getTexture(block *b) override;
	};
	
	class multiStableAnimator : public animator {
	private:
		UVoffset* uv; 
		int l;
	public:
		multiStableAnimator(UVoffset* t, int len);
		~multiStableAnimator();
		
		void stateFunction(block *b) override;
		UVoffset getTexture(block *b) override;
	};
}

#endif
