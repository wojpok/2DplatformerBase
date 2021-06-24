#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;
in vec2 ou;
in vec3 worldOffset;
in float time_f;
// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;

vec2 squareImaginary(vec2 number){
	return vec2(
		pow(number.x,2)-pow(number.y,2),
		2*number.x*number.y
	);
}

float iterateMandelbrot(vec2 coord){
	
	vec2 z = vec2(sin(time_f/10)*.75,cos(time_f/10)*.75);
	
	for(float i=0;i<100;i++){
		z = squareImaginary(z) + coord;
		if(length(z)>2) return i/100.0;
	}
	return 1.0;
}

void main(){
	if(ou.y == 0 && ou.x == 0) {
		color = vec4(0,0,0,0);
	}
	else {
	vec2 UVs = 0.25*(UV + /*vec2(0.5, 0.5)*/ vec2(ou.y, ou.x));
	
	//float it = iterateMandelbrot(vec2((worldOffset.z-8)/8+0.25*UV.x, (worldOffset.y-8)/8+0.25*UV.y));
	
	// Output color = color of the texture at the specified UV
	//color = vec4 ( texture( myTextureSampler, UVs ).rgb, it);
	//color = vec4(1, 1, 1, 1) * it;
	color = texture( myTextureSampler, UVs ).rgba;
	}
}


