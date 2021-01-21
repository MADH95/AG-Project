#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform sampler2D stencilMask;

const float offset = 1.0 / 300.0;

void main()
{
	vec2 offsets[9] = vec2[](
		vec2(-offset, 	offset), // top-left
		vec2( 0.0f, 	offset), // top-middle
		vec2( offset, 	offset), // top-right
		vec2(-offset,	0.0f),	 // center-left
		vec2( 0.0f, 	0.0f),	 //center
		vec2( offset, 	0.0f),	 //center-right
		vec2(-offset,  -offset), //bottom-left
		vec2( 0.0f,    -offset), //bottom-middle
		vec2( offset,  -offset)  //bottom-right
	);
	
	float kernal[9] = float[](
		-1, -1, -1,
		-1,  9, -1,
		-1, -1, -1
	);
	
	float mask = texture(stencilMask, TexCoords).r;
	vec3 color = vec3(0.0);
	
	if(mask == 0.0)
	{
		color = texture(screenTexture, TexCoords).rgb;
	}
	else
	{
		for(int i = 0; i < 9; i++)
		{
			color += vec3(texture(screenTexture, TexCoords.st + offsets[i])) * kernal[i];
		}
	}
	
	FragColor = vec4(color, 1.0);
}