#ifndef BLOCKS_HPP_
#define BLOCKS_HPP_

/*
 * 	Block definitions. Each block implements certain state-specific functions when needed
 *  In this example lamp (which implements Game of Life mechanics) needs more sophisticated intervalState function.
 */

namespace obj {
	
	class animator;
	// TO DO SOMETIME IN THE FUTURE: declare each block in seperate file

	class block {
	public:
		const uint8_t id = 0;
		
		static block* createInstance();
		static animator* anim;
		
		virtual animator* gAnim();
		
		virtual void  updateState();
		virtual void  interState();
		virtual int   getState();
	};
	
	class grass : public block {
	public:
		static block* createInstance();
		
		const uint8_t id = 1;
		static animator* anim;	
		animator* gAnim();
	};
	
	class dirt : public block {
	public:
		static block* createInstance();
		
		const uint8_t id = 2;
		static animator* anim;	
		animator* gAnim();
	};
	
	class stone : public block {
	public:
		static block* createInstance();
		
		const uint8_t id = 3;
		static animator* anim;
		
		stone();
		virtual int   getState() override;
		animator* gAnim() override;
		
		int state;
	};
	
	class wood : public block {
	public:
		static block* createInstance();
		
		const uint8_t id = 4;
		static animator* anim;	
		animator* gAnim();
	};
	
	class leaf : public block {
	public:
		static block* createInstance();
		
		const uint8_t id = 5;
		static animator* anim;	
		animator* gAnim();
	};
	
	class lamp : public block {
	public:
		static block* createInstance();
		
		const uint8_t id = 6;
		static animator* anim;
		
		lamp();
		virtual void  updateState() override;
		virtual int   getState() override;
		virtual void  interState() override;
		animator* gAnim() override;
		
		int state;
	};
	
	class boiler : public block {
	public:	
		static block* createInstance();
		
		const uint8_t id = 7;
		static animator* anim;
		animator* gAnim();
	};
	
	class planking : public block {
	public:	
		static block* createInstance();
		
		const uint8_t id = 8;
		static animator* anim;
		animator* gAnim();
	};
	
	class bricks : public block {
	public:	
		static block* createInstance();
		
		const uint8_t id = 9;
		static animator* anim;
		animator* gAnim();
	};
}

#endif
