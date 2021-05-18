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
	
	class fan : public block {
	public:	
		const uint8_t id = 2;
		static animator* anim;
		animator* gAnim() override;
	};
	
	class random : public block {
	public:
		const uint8_t id = 5;
		static animator* anim;
		
		random();
		virtual void  updateState() override;
		virtual int   getState() override;
		virtual void  interState() override;
		animator* gAnim() override;
		
		float time;
		int state;
	};
	
	class lamp : public random {
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
	};
}

#endif
