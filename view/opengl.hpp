#ifndef OPENGL_HPP_
#define OPENGL_HPP_

namespace view {
	
	//wrapper functions for onpegl. It helps keep main.cpp as tidy as possible
	void createContext();
	void clearFrame();
	void pushFrame();
	bool isContextOpen();
	void clearContext();

	void refreshFuncSet(void (*ptr)());

	// shader class - stores required shader and some of it uniform variables
	// also contains draw functions
	class shader {
	public:
		GLuint Shader;
		GLuint MVPID;
		GLuint Pos1ID;
		GLuint Pos2ID;
		GLuint TextureID;
		
		void useProgram();
		void bindTexture(GLuint Texture);
		virtual void bindMVP(glm::mat4 MVP);
		void bindPos(glm::mat4 Pos);
		void bindPos2(glm::mat4 Pos);
	};
	
	// shape class - provides buffers with mesh UVs and Vertices
	class shape {
	private:
		GLuint vertexBuffer;
		GLuint uvBuffer;
		int bufferSize;	
		
	public:
		shape(GLuint vb, GLuint ub, int bs);
		void draw();
		void drawInstantiated(int count);
		~shape();
	};
	
	
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	void computeMatricesFromInputs(glm::mat4 camCenter);
	
	// file loaders
	GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
	GLuint loadBMP_custom(const char * imagepath);
}


#endif
