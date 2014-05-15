#version 400

struct Material{
	vec3 Kd;
	vec3 Ka;
	vec3 Ks;
	float Shininess;
	float ReflectFactor;
};

struct Light{
	int type;//0:directional  1:point  2:spot
	vec4 pos;
	vec4 dir;
	float spotCutOff;//cos(a)
	vec3 specular;
	vec3 diffuse;
	vec3 ambient;
};

uniform Material material;
uniform Light light[1];//to add more light, increment array size, update ads()
uniform sampler2D TexID;//texture unit

/* UNCOMMENT FOR SKY BOX REFLECTION (1/2)*/
/*uniform samplerCube CubeMapTex;//sky box texture // for reflection */

/* UNCOMMENT FOR MOSS TEXTURE (1/2)*/
/*uniform sampler2D MossTex;//moss texture unit */

in vec3 position;//position in world
in vec3 normal;//normal in world
in vec2 texCoord;//texture coordinate
flat in vec3 cam;//camera in world

layout (location=0) out vec4 FragColor;

vec3 norm;//norm based on facing

uniform sampler2D shadowMap;
in vec3 shadow_coord;//shadow 
float lit=1;

vec4 myads(vec4 TexColor){
	vec4 ads=vec4(0.0,0.0,0.0,1.0);
	vec3 n = normalize(norm);
	vec3 s,v,r;

	//light[0]
	if(light[0].type==0){
		s = normalize( vec3(light[0].pos));
	}else{
		s = normalize( vec3(light[0].pos)-position);
	}
	v = normalize(vec3(cam-position));
	r = reflect(-s,n);
	
	if( light[0].type!=2 ){//directional and point light
		ads += max(TexColor*vec4(light[0].ambient,1.0),
		           TexColor*vec4(light[0].diffuse*max(dot(s,n),0.0),1.0)*lit
		           + vec4(light[0].specular,1.0)*pow(max(dot(r,v),0.0), material.Shininess)*lit);
	}else if( light[0].type==2 && dot(normalize(vec3(-light[0].dir)),s) >= light[0].spotCutOff){//spot light
		ads += (dot(normalize(vec3(-light[0].dir)),s)-light[0].spotCutOff)/(1-light[0].spotCutOff)//for soft edge
				*max(TexColor*vec4(light[0].ambient,1.0), 
				     TexColor*vec4(light[0].diffuse*max(dot(s,n),0.0),1.0)*lit 
				     + vec4(light[0].specular,1.0)*pow(max(dot(r,v),0.0), material.Shininess)*lit);
	}

	return ads;
}

void main()
{
	vec4 ads=vec4(0.0,0.0,0.0,0.0);

	norm = normal;

	// uncomment to enable shadow 
	// float depth = texture(shadowMap,vec2(shadow_coord[0],shadow_coord[1])).x;
   	// if(shadow_coord[2]<=depth+0.0002)
	//   	lit=1;
	//  else
	//  	lit=0;

	//apply texture
	vec4 texColor = texture( TexID, texCoord );

	//apply light
	texColor = myads(texColor);

	ads+=texColor;

	FragColor = ads;

}