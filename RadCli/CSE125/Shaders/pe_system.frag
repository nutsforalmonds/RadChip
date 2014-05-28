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
   
// Varying                    
in vec3 v_pColorOffset;
in float v_Growth;
in float v_Decay;
in vec3 position;
flat in vec3 cam;//camera in world
					
// Uniforms
uniform highp float     u_Time;
uniform highp vec3      u_eColorStart;
uniform highp vec3      u_eColorEnd;
uniform sampler2D		u_Texture;

//uniform vec3 uColor;
//uniform sampler2D uTexture;
						
out vec4 FragColor;                                                                 
                                                                                    
void main()                                                                         
{      
	// Texture
	vec4 texture = texture2D(u_Texture, gl_PointCoord);

	// Color
    highp vec4 color = vec4(1.0);
    
	// If blast is growing
    if(u_Time < v_Growth)
    {
        color.rgb = u_eColorStart;
    }
 
    // Else if blast is decaying
    else
    {
        highp float time = (u_Time - v_Growth) / v_Decay;
        color.rgb = mix(u_eColorStart, u_eColorEnd, time);
    }
 
    color.rgb += v_pColorOffset;
    color.rgb = clamp(color.rgb, vec3(0.0), vec3(1.0));
 
    //Outputs
    gl_FragColor = texture * color;

	//apply fog
	float dist = distance(position,cam);
	float fog_factor = (dist-fog.minDist)/(fog.maxDist-fog.minDist);
	fog_factor = pow(clamp(fog_factor,0.0,1.0),2.0)*fog.visibility;
	gl_FragColor = mix(gl_FragColor,vec4(fog.color,1.0),fog_factor); 
}