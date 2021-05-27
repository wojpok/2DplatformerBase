#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 3) in vec3 instanceMatrix;
layout(location = 4) in vec2 atlasUVs;

// Output data ; will be interpolated for each fragment.
out vec2 UV;
out vec2 ou;
out vec3 worldOffset;
// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 offset;
//uniform mat4 offset2;

void main(){

	// Output position of the vertex, in clip space : MVP * position
	vec3 o = vertexPosition_modelspace + instanceMatrix;
	gl_Position =  MVP * offset * vec4(o,1);
	
	// UV of the vertex. No special space for this one.
	UV = vertexUV;
	ou = atlasUVs;
	worldOffset = instanceMatrix;
}

