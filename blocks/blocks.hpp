#ifndef BLOCKS_HPP_
#define BLOCKS_HPP_

namespace obj {
	
	class animator;
	
	class block {
	public:
		const uint8_t id = 0;
		static const animator* anim;
		
		virtual float getTime();
		virtual int   getState();
		virtual void  setState(int s);
	};
	
	class stone : public block {
	public:	
		const uint8_t id = 2;
		static const animator* anim;
		/*float getTime();
		int   getState();
		void  setState();*/
	};
	
	class lamp : public block {
	public:
		const uint8_t id = 5;
		static const animator* anim;
		
		lamp();
		float getTime();
		int   getState();
		void  setState(int s);
		
		float time;
		int state;
	};
}

#endif
