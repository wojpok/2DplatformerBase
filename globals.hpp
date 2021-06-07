#ifndef GLOBALS_HPP
#define GLOBALS_HPP

// bad practise, but I'll rewrite this in the future to secure data

#ifndef NOTCON
extern con::chunk *ch;
#endif

extern float blockScale;

extern glm::mat4 MVP;
extern glm::mat4 scaledMVP;

extern glm::mat4 centreTransfromation;

extern int windowHeight;
extern int windowWidth;

#endif
