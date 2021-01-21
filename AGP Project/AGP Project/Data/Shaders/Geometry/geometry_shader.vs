#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

out VS_OUT {
	vec2 TexCoords;
	vec3 FragPos;
	vec3 Normal;
	mat3 TBN;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec4 worldPos = model * vec4(aPos, 1.0);
    vs_out.FragPos = worldPos.xyz;
    vs_out.TexCoords = aTexCoords;
	
	vec3 T = normalize(mat3(model) * aTangent);
	vec3 B = normalize(mat3(model) * aBitangent);
	vec3 N = normalize(mat3(model) * aNormal);
	vs_out.TBN = transpose(mat3(T, B, N));
	
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vs_out.Normal = normalMatrix * aNormal;

    gl_Position = projection * view * worldPos;
}