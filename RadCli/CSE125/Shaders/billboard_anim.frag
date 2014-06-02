#version 400                                                                       
                                  
struct FogInfo{
	float maxDist;
	float minDist;
	vec3 color;
	float visibility;
	float maxHeight;
	float minHeight;
};
uniform FogInfo fog;

uniform sampler2D texUnit;                                                        
                                                                                    
in vec2 TexCoord;
in vec3 world_pos;
flat in vec3 world_cam;                                                                        
out vec4 FragColor;                                                                 
                                                                                    
void main()                                                                         
{                                                                                   
    FragColor = texture2D(texUnit, TexCoord);                                     
    
    //apply fog
	float dist = distance(world_pos,world_cam);
	float fog_factor = (dist-fog.minDist)/(fog.maxDist-fog.minDist);
	fog_factor = pow(clamp(fog_factor,0.0,1.0),2.0)*fog.visibility;

	FragColor = vec4(mix(FragColor.xyz,fog.color ,fog_factor),FragColor[3]);                                                              
}