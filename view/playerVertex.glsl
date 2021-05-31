#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

// Output data ; will be interpolated for each fragment.
out vec2 UV;
out float time_f;
// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 offset;
uniform float time;
//uniform mat4 offset2;

void main(){

	// Output position of the vertex, in clip space : MVP * position
	vec3 o = vertexPosition_modelspace;
	gl_Position =  MVP * offset * vec4(o,1);
	
	// UV of the vertex. No special space for this one.
	UV = vertexUV;
	time_f = time;
}

