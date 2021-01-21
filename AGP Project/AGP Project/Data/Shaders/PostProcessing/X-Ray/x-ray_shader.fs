#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform sampler2D stencilMask;

void main()
{
	float mask = texture(stencilMask, TexCoords).r;
	vec4 color = texture(screenTexture, TexCoords);
	
	if (mask == 0.0)
	{
		FragColor = color;
	}
	else
	{
		FragColor = vec4(vec3(1.0 - color), 1.0);
	}
}