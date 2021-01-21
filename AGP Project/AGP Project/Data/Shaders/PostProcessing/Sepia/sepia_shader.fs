#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform sampler2D stencilMask;

const float offset = 1.0 / 300.0;

void main()
{
	float mask = texture(stencilMask, TexCoords).r;
	vec3 color = texture(screenTexture, TexCoords).xyz;
	
	if(mask == 0.0)
	{
		FragColor = vec4(color, 1.0);
	}
	else
	{
		FragColor.r = min((color.r * 0.393) + (color.g * 0.769) + (color.b * 0.189), 255.0);
		FragColor.g = min((color.r * 0.249) + (color.g * 0.686) + (color.b * 0.168), 255.0);
		FragColor.b = min((color.r * 0.272) + (color.g * 0.534) + (color.b * 0.131), 255.0);
		FragColor.a = 1.0;
	}
}