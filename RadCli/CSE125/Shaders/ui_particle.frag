#version 400                                                                       
                    
in vec3 vShade;
					
uniform vec3 uColor;
uniform sampler2D uTexture;
						
out vec4 FragColor;                                                                 
                                                                                    
void main()                                                                         
{       
	vec4 texture = texture2D(uTexture, gl_PointCoord);
	
	vec4 color = vec4((uColor+vShade), 1.0);
	color.rgb = clamp(color.rgb, vec3(0.0), vec3(1.0));
    //gl_FragColor = color;
	
    //gl_FragColor = vec4(uColor, 1.0);
	
	//vec4 color = vec4(uColor, 1.0);
	gl_FragColor = texture * color;
}