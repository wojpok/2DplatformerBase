#ifndef PLAYER_HPP_
#define PLAYER_HPP_

namespace con {

	class player {
	public:
		//change: there is no animator
		//			textures don't support opacity (yet) so simple look is 
		//			hard-coded into player shader
	
		glm::mat4 worldspacePos;
		view::shader* playerShader;
		view::shape*  playerMesh;
		
		void update();
		void draw(glm::mat4 MVP);
		
	};

}

#endif
