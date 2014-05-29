#version 400

/* UNCOMMENT FOR FOG EFFECT (1/2)*/
struct FogInfo{
	float maxDist;
	float minDist;
	vec3 color;
	float visibility;
	float maxHeight;
	float minHeight;
};
uniform FogInfo fog;

struct Light{
	int type;//0:directional  1:point  2:spot
	vec4 pos;
	vec4 dir;
	float spotCutOff;//cos(a)
	vec3 specular;
	vec3 diffuse;
	vec3 ambient;
};

uniform Light light[1];//one light for basic shader. To add light, increment light array size, then update ads()

/* UNCOMMENT FOR SKY BOX REFLECTION (1/2)*/
/*uniform samplerCube CubeMapTex;//sky box texture // for reflection */

in vec3 WorldPos_FS_in;                                                                        
in vec2 TexCoord_FS_in;            
flat in vec3 CamPos_FS_in;     
in vec3 shadow_coord;    

uniform vec3 color;
uniform float width;

uniform	sampler2D colorTex;
uniform sampler2D occlusionTex;
uniform sampler2D specularTex;
uniform sampler2D normalTex;
uniform sampler2D shadowMap;
//uniform sampler2DShadow shadowMap;

float lit;

layout (location=0) out vec4 FragColor;

vec3 norm;//norm based on facing, decided in main()

vec3 texDiffuse;
vec3 texSpecular;
vec3 texOcc;

vec4 myads(){
	vec4 ads=vec4(0.0,0.0,0.0,1.0);
	vec3 n = normalize(norm);
	vec3 s,v,r;

	//light[0]
	if(light[0].type==0){
		s = normalize( vec3(light[0].pos));
	}else{
		s = normalize( vec3(light[0].pos)-WorldPos_FS_in);
	}
	v = normalize(vec3(CamPos_FS_in-WorldPos_FS_in));
	r = reflect(-s,n);
	if( light[0].type!=2 ){//direction light and point light
		ads += max( vec4(light[0].ambient*texDiffuse,1.0), 
		            vec4(light[0].diffuse*texDiffuse*max(dot(s,n),0.0)*lit,1.0)
		            + vec4(light[0].specular*texSpecular*pow(max(dot(r,v),0.0), 10)*lit,1.0)); //Shininess = 10
	}else if( light[0].type==2 && dot(normalize(vec3(-light[0].dir)),s) >= light[0].spotCutOff){//spot light
		ads += (dot(normalize(vec3(-light[0].dir)),s)-light[0].spotCutOff)/(1-light[0].spotCutOff)//to make soft edge
			   * max( vec4(light[0].ambient*texDiffuse,1.0),  
			          vec4(light[0].diffuse*texDiffuse*max(dot(s,n),0.0)*lit,1.0)
			          + vec4(light[0].specular*texSpecular*pow(max(dot(r,v),0.0), 10)*lit,1.0)); //Shininess = 10
	}

	return vec4(ads.xyz*texOcc.xyz,1.0);
	//return ads;
}

//uniform float Depth[5];
//uniform int num = 5;

void main()
{
	vec4 nt = texture(normalTex, TexCoord_FS_in);
	vec3 normal = 2*vec3(nt[0],nt[2],nt[1])-vec3(1.0,1.0,1.0);//normal = vec3(ModelMatrix*vec4(VertexNormal,0));

	if(gl_FrontFacing){
		norm = normal;
	}else{
		norm = -normal;
	}

	vec4 ct = texture(colorTex,TexCoord_FS_in);
	vec4 st = texture(specularTex,TexCoord_FS_in);
	vec4 ot = texture(occlusionTex,TexCoord_FS_in);

	texDiffuse = ct.xyz;
	texSpecular = st.xyz;
	texOcc = ot.xyz;

  	float depth = texture(shadowMap,vec2(shadow_coord[0],shadow_coord[1])).x;
  	if(shadow_coord[2]<=depth+0.000025)
	  	lit=1;
	else
		lit=0;

	  // lit=0;
	  // float depth;
	  // for(float i=-1.5/1024;i<=1.5/1024;i+=1.0/1024){
	  // 	for(float j=-1.5/1024;j<=1.5/1024;j+=1.0/1024){
	  // 		depth = texture(shadowMap,vec2(shadow_coord[0]+i,shadow_coord[1]+j)).x;
	  // 		if(shadow_coord[2]<=depth+0.00015)
	  // 			lit+=1;
	  // 	}
	  // }
	  // lit = lit/16.0;

	  // lit=0;
	  // float depth;

	  // float midv =  shadow_coord[1]-mod(shadow_coord[1],1/1024.0) + 0.5/1024.0;
	  // float midh =  shadow_coord[0]-mod(shadow_coord[0],1/1024.0) + 0.5/1024.0;

	  // int hc = 0;
	  // float hor[3];
	  // for(float i=-1.0/1024;i<=1.0/1024;i+=1.0/1024){
	  // 	int vc = 0;
	  // 	float ver[3];
	  // 	for(float j=-1.0/1024;j<=1.0/1024;j+=1.0/1024){
	  // 		depth = texture(shadowMap,vec2(shadow_coord[0]+i,shadow_coord[1]+j)).x;
	  // 		if(shadow_coord[2]<=depth+0.0001){
	  // 			ver[vc] = 1;
	  // 		}else{
	  // 			ver[vc] = 0;
	  // 		}
	  // 		vc++;
	  // 	}
	  // 	if(shadow_coord[1]>=midv){
	  // 		hor[hc] = ver[1] + (shadow_coord[1]-midv)/(0.5/1024)*(ver[2]/2.0 - ver[1]/2.0); 
	  // 	}else{
			// hor[hc] = ver[1] + (midv-shadow_coord[1])/(0.5/1024)*(ver[0]/2.0 - ver[1]/2.0); 
	  // 	}
	  // 	hc++;
	  // }
	  // if(shadow_coord[0]>=midh){
	  // 		lit = hor[1] + (shadow_coord[0]-midh)/(0.5/1024)*(hor[2]/2.0 - hor[1]/2.0); 
	  // 	}else{
			// lit = hor[1] + (midh-shadow_coord[0])/(0.5/1024)*(hor[0]/2.0 - hor[1]/2.0); 
	  // 	}

	/* UNCOMMENT FOR SKYBOX REFLECTION (2/2) */
	/* //apply skybox reflection
	vec3 reflectDir = reflect(WorldPos_FS_in-CamPos_FS_in,normalize(norm));
	vec4 cubeMapColor = texture(CubeMapTex,reflectDir);
	ads = mix(ads,cubeMapColor,material.ReflectFactor);
	//ads = mix(ads,cubeMapColor,1-(1-material.ReflectFactor)*dot(normalize(reflectDir),normalize(norm))); for more complex reflect */

	vec4 ads = myads();

	/* UNCOMMENT FOR FOG EFFECT (2/2)*/
	//apply fog
	float dist = distance(WorldPos_FS_in,CamPos_FS_in);
	float fog_factor = (dist-fog.minDist)/(fog.maxDist-fog.minDist);
	fog_factor = pow(clamp(fog_factor,0.0,1.0),2.0)*fog.visibility;
	ads = mix(ads,vec4(fog.color,1.0),fog_factor); 

	FragColor = ads; 
}