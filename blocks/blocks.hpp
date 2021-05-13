#ifndef BLOCKS_HPP_
#define BLOCKS_HPP_

namespace obj {
	
	class animator;
	
	class block {
	public:
		const uint8_t id = 0;
		static animator* anim;
		
		virtual animator* gAnim();
		
		virtual float getTime();
		virtual int   getState();
		virtual void  setState(int s);
	};
	
	class stone : public block {
	public:	
		const uint8_t id = 2;
		static animator* anim;
		animator* gAnim() override;
		//static animator* anim;
		/*float getTime();
		int   getState();
		void  setState();*/
	};
	
	class lamp : public block {
	public:
		const uint8_t id = 5;
		static animator* anim;
		
		lamp();
		float getTime() override;
		int   getState() override;
		void  setState(int s) override;
		
		float time;
		int state;
	};
}

#endif
