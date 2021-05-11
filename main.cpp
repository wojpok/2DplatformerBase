#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "view/opengl.hpp"
#include "blocks/blocks.hpp"



int main() {
	std::cout<<" Welcome to 2D platformer "<<std::endl;
	
	view::createContext();
	
	view::shader basic; 
	basic.Shader = view::LoadShaders("view/basicVertex.glsl","view/basicFragment.glsl");
	basic.TextureID = glGetUniformLocation(basic.Shader, "myTextureSampler");
	basic.MVPID = glGetUniformLocation(basic.Shader, "MVP");
	basic.PosID = glGetUniformLocation(basic.Shader, "offset");
	
	GLuint grass = view::loadBMP_custom("blocks/simplegrass.bmp");
	
	glm::mat4 none = glm::mat4(1);
	
	glm::mat4 offset = glm::mat4(1);
	
	
		basic.bindTexture(grass);
	
	
	do { 
		view::clearFrame();
		
		view::computeMatricesFromInputs();
		
		glm::mat4 ProjectionMatrix = view::getProjectionMatrix();
		glm::mat4 ViewMatrix = view::getViewMatrix();
		glm::mat4 ModelMatrix = glm::mat4(1);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		MVP = glm::scale(MVP, glm::vec3(0.125f, 0.125f, 0.125f));
		
		basic.useProgram();	
		basic.bindMVP(MVP);
		basic.bindPos(offset);
		offset[3][2] += view::getDeltaTime()*10;
		
		view::getBlock()->draw();
		
		view::pushFrame();
	}
	while(view::isContextOpen() );
	
	view::clearContext();
	
	return 0;
}
