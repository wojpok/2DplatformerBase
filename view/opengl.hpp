#ifndef OPENGL_HPP_
#define OPENGL_HPP_

namespace view {
	static GLFWwindow* window;
	
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
		
		void bindTexture(GLuint Texture);
		void bindMVP(glm::mat4 MVP);
		void bindPos(glm::mat4 Pos);
		
	};
	
	class shape {
	public:
		GLuint vertexBuffer;
		GLuint uvBuffer;
		int bufferSize;	
	
		shape(GLuint vb, GLuint ub, int bs);
		void draw(GLuint PositionID, glm::vec3 pos, GLuint Texture, GLuint TextureID);
		~shape();
	};
	
	GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
	GLuint loadBMP_custom(const char * imagepath);
}


#endif
