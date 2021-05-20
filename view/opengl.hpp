#ifndef OPENGL_HPP_
#define OPENGL_HPP_

namespace view {
	extern GLFWwindow* window;
	extern float deltaTime;
	extern float frameL;
	extern int frameCnt;
	
	void createContext();
	void clearFrame();
	void pushFrame();
	bool isContextOpen();
	void clearContext();

	void refreshFuncSet(void (*ptr)());

	class shader {
	public:
		GLuint Shader;
		GLuint MVPID;
		GLuint Pos1ID;
		GLuint Pos2ID;
		GLuint TextureID;
		
		void useProgram();
		void bindTexture(GLuint Texture);
		virtual void bindMVP(glm::mat4 MVP); //Trzeba to wywołać w każdej klatce, ale tylko raz
		void bindPos(glm::mat4 Pos);
		void bindPos2(glm::mat4 Pos);
	};
	
	class shape {
	public:
		GLuint vertexBuffer;
		GLuint uvBuffer;
		int bufferSize;	
	
		shape(GLuint vb, GLuint ub, int bs);
		void draw();
		void drawInstantiated(int count);
		~shape();
	};
	
	extern shape* block;
	
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	void computeMatricesFromInputs();
	
	GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
	GLuint loadBMP_custom(const char * imagepath);
}


#endif
