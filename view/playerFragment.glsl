#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;
in float time_f;
// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.
//uniform sampler2D myTextureSampler;

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
	//vec2 UVs = 0.25*(UV);
	
	float it = iterateMandelbrot(2*(UV-vec2(0.5, 0.5)));
	
	// Output color = color of the texture at the specified UV
	//color = vec4 ( texture( myTextureSampler, UVs ).rgb, it);
	/*color = vec4(0.5*sin(2*time_f)+0.5, 
				 0.5*sin(3*time_f)+0.5,  
				 0.5*sin(5*time_f)+0.5, 1)*it;*/
	 color = vec4(it, it, it, it);
	//color = texture( myTextureSampler, UVs ).rgba;
}


