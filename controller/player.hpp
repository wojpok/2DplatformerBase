#ifndef PLAYER_HPP_
#define PLAYER_HPP_

namespace con {

	class player {
	public:
		glm::mat4 worldspacePos;
		view::shader* playerShader;
		view::shape*  playerMesh;
		
		void update();
		void draw(glm::mat4 MVP);
		
	};

}

#endif
