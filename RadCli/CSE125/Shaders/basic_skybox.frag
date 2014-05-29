#version 400

/* UNCOMMENT FOR FOG (1/2)*/
struct FogInfo{
	float maxDist;
	float minDist;
	vec3 color;
	float visibility;
	float maxHeight;
	float minHeight;
};
uniform FogInfo fog;

uniform samplerCube CubeMapTex;//sky box texture unit

in vec3 position;//position in world
in vec3 normal;//normal in world
flat in vec3 cam;//camera in world

layout (location=0) out vec4 FragColor;

void main()
{
	vec4 ads=vec4(0.0,0.0,0.0,1.0);

	//apply cube map
	vec3 skyDir = position-cam;
	vec4 cubeMapColor = texture(CubeMapTex,skyDir);
	ads += cubeMapColor;

	/* UNCOMMENT FOR FOG (2/2)*/
	//apply fog
	//ads = mix(ads,vec4(fog.color,1.0),fog.visibility); 

	float height = position.y-4;
	float height_factor;
	if(height>=0){
		height_factor = (fog.maxHeight-height)/(fog.maxHeight-fog.minHeight);
		height_factor = pow(clamp(height_factor,0.0,1.0),2.0)*fog.visibility;
	}else{
		height_factor = fog.visibility;
	}
	ads = mix(ads,vec4(fog.color,1.0),height_factor);

	FragColor = ads;
}