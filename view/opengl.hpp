#ifndef OPENGL_HPP_
#define OPENGL_HPP_

namespace view {
	extern GLFWwindow* window;
	extern float deltaTime;
	
	void createContext();
	void clearFrame();
	void pushFrame();
	bool isContextOpen();
	void clearContext();

	class shader {
	public:
		GLuint Shader;
		GLuint MVPID;
		GLuint PosID;
		GLuint TextureID;
		
		void useProgram();
		void bindTexture(GLuint Texture);
		virtual void bindMVP(glm::mat4 MVP); //Trzeba to wywołać w każdej klatce, ale tylko raz
		void bindPos(glm::mat4 Pos);
		
	};
	
	class shape {
	public:
		GLuint vertexBuffer;
		GLuint uvBuffer;
		int bufferSize;	
	
		shape(GLuint vb, GLuint ub, int bs);
		void draw();
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
