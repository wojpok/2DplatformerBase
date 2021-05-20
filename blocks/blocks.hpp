#ifndef BLOCKS_HPP_
#define BLOCKS_HPP_

namespace obj {
	
	class animator;
	
	class block {
	public:
		const uint8_t id = 0;
		static animator* anim;
		
		virtual animator* gAnim();
		
		virtual void  updateState();
		virtual void  interState();
		virtual int   getState();
	};
	
	class grass : public block {
	public:
		const uint8_t id = 1;
		static animator* anim;	
		animator* gAnim();
	};
	
	class dirt : public block {
	public:
		const uint8_t id = 2;
		static animator* anim;	
		animator* gAnim();
	};
	
	class leaf : public block {
	public:
		const uint8_t id = 5;
		static animator* anim;	
		animator* gAnim();
	};
	
	class water_surface : public block {
	public:	
		const uint8_t id = 7;
		static animator* anim;
		animator* gAnim();
	};
	
	class stone : public block {
	public:
		const uint8_t id = 3;
		static animator* anim;
		
		stone();
		virtual int   getState() override;
		animator* gAnim() override;
		
		int state;
	};
	
	/*class lamp : public random {
	public:
		const uint8_t id = 7;
		static animator* anim;
		
		lamp();
		virtual void  updateState() override;
		virtual int   getState() override;
		virtual void  interState() override;
		animator* gAnim() override;
		
		float time;
		int state;
	};*/
}

#endif
