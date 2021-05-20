#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;
in vec2 ou;

// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;

void main(){
	if(ou.y == 0 && ou.x == 0) {
		color = vec4(0,0,0,0);
	}
	else {
	vec2 UVs = 0.25*(UV + vec2(ou.y, ou.x));
	
	// Output color = color of the texture at the specified UV
	color = texture( myTextureSampler, UVs ).rgba;
	}
}
