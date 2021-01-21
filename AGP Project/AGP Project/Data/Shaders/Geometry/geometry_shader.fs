#version 330 core

struct Material {
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
	sampler2D texture_height1;
	bool hasHeightMap;
};

layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

in VS_OUT {
	vec2 TexCoords;
	vec3 FragPos;
	vec3 Normal;
	mat3 TBN;
} fs_in;

uniform Material material;
uniform vec3 viewPos;

void main()
{
	vec2 texCoords = fs_in.TexCoords;
	vec3 fragPos = fs_in.FragPos;
	
	if(material.hasHeightMap)
	{
		fragPos = fs_in.TBN * fragPos;
		vec3 viewDir = -normalize(fragPos - viewPos);
		viewDir = normalize(fs_in.TBN * viewDir);
		
		float heightScale = 0.025;
		float bias = heightScale / 2.0;
		float height = texture(material.texture_height1, texCoords).r;
		vec2 halfOffset = normalize(viewDir).xy * (height * heightScale - bias);
		
		for (int i = 0; i < 2; i++)
		{
			height = (height + texture(material.texture_height1, texCoords + halfOffset).r) * 0.5;
			halfOffset = normalize(viewDir).xy * (height * heightScale - bias);
		}
		texCoords = texCoords + halfOffset;
	}
	
    // store the fragment position vector in the first gbuffer texture
    gPosition = fs_in.FragPos;
    // also store the per-fragment normals into the gbuffer
    gNormal = normalize(fs_in.Normal);
    // and the diffuse per-fragment color
    gAlbedoSpec.rgb = texture(material.texture_diffuse1, texCoords).rgb;
    // store specular intensity in gAlbedoSpec's alpha component
    gAlbedoSpec.a = texture(material.texture_specular1, texCoords).r;
}