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
		float average = 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
		FragColor = vec4(average, average, average, 1.0);
	}
}