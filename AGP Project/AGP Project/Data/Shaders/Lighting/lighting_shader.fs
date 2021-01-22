#version 330 core
layout (location = 0) out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;
uniform sampler2D depthMap;

struct Light {
    //vec3 Position; //not used for directional lighting
    vec3 Direction;
	vec3 Color;
    
	//Used for point lights and spotlights
	//float Constant;
    //float Linear;
    //float Quadratic;
	//float Radius;
};

uniform Light light;
uniform vec3 viewPos;
uniform mat4 lightSpaceMatrix;

vec3 CalcDirLight(vec3 FragPos, vec3 Normal, vec3 Diffuse, float Specular);
float CalcShadow(vec3 LightDir, vec3 Normal, vec3 FragPos);

void main()
{             
    // retrieve data from gbuffer
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Normal = texture(gNormal, TexCoords).rgb;
    vec3 Diffuse = texture(gAlbedoSpec, TexCoords).rgb;
    float Specular = texture(gAlbedoSpec, TexCoords).a;
    
    // then calculate lighting as usual
    vec3 lighting  = CalcDirLight(FragPos, Normal, Diffuse, Specular);
	
    FragColor = vec4(lighting, 1.0);
}

vec3 CalcDirLight(vec3 FragPos, vec3 Normal, vec3 Diffuse, float Specular)
{
    vec3 viewDir  = normalize(viewPos - FragPos);
	
    // calculate distance between light source and current fragment
    //float distance = length(light.Position - FragPos); // not used for directional lighting
	
	// ambient
	vec3 ambient = Diffuse * 0.8; // hard-coded ambient component
    // diffuse
    vec3 lightDir = normalize(-light.Direction);
    vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Diffuse * light.Color;
    // specular
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(Normal, halfwayDir), 0.0), 16.0);
    vec3 specular = light.Color * spec * Specular;
    // attenuation - not used for directional lighting
    //float attenuation = 1.0 / (light.Constant + light.Linear * distance + light.Quadratic * distance * distance);
    // shadow
	float shadow = CalcShadow(lightDir, Normal, FragPos);
	
	//combine results
	//ambient *= attenuation;
	//diffuse *= attenuation;
    //specular *= attenuation;
    
	return ambient + (shadow * (diffuse + specular));
}

float CalcShadow(vec3 LightDir, vec3 Normal, vec3 FragPos)
{
	//calculate frag position in light space
	vec4 fragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);
	
	//project coordinates
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	projCoords = projCoords * 0.5 + 0.5;
	
	//depth calculations
	float closestDepth = texture(depthMap, projCoords.xy).r;
	float currentDepth = projCoords.z;
	
	float bias = max(0.012 * (1.0 - dot(Normal, LightDir)), 0.005);
	
	float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(depthMap, 0);
	for (int x = -1; x <= 1; ++x)
	{
		for (int y = -1; y <= 1; ++y)
		{
			float pcfDepth = texture(depthMap, projCoords.xy + vec2(x, y) * texelSize).r;
			shadow += (currentDepth - bias > pcfDepth ? 1.0 : 0.0);
		}
	}
	shadow /= 9.0;
	
	if(projCoords.z > 1.0)
		shadow = 0.0;
		
	return 1.0 - shadow;
}