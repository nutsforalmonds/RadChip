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
uniform float transparency;
uniform int sample_x;
uniform int sample_y;
uniform float x_dist;
uniform float y_dist;  
uniform float blur_strength;                                          
                                                                                    
in vec2 TexCoord;
in vec3 world_pos;
flat in vec3 world_cam;                                                                        
out vec4 FragColor;                                                                 
                                                                                    
void main()                                                                         
{                                                                                   
    FragColor = texture2D(texUnit, TexCoord);                                     
    
    //glow
    if(sample_x!=0 || sample_y!=0){
    	for(int i=-sample_x;i<sample_x+1;i++){
	    	for(int j=-sample_y;j<sample_y+1;j++){
	    		vec4 add_on_color = texture2D(texUnit, TexCoord+vec2(i*x_dist,j*y_dist));
	    		add_on_color = vec4(add_on_color.xyz*add_on_color[3] , add_on_color[3])*blur_strength/((2*sample_x+1)*(2*sample_y+1));
	    		FragColor += add_on_color;
	    	}
   		}
    }

    //apply fog
	float dist = distance(world_pos,world_cam);
	float fog_factor = (dist-fog.minDist)/(fog.maxDist-fog.minDist);
	fog_factor = pow(clamp(fog_factor,0.0,1.0),2.0)*fog.visibility;

	FragColor = vec4(mix(FragColor.xyz,fog.color ,fog_factor),FragColor[3]*transparency);                                                              
}