#version 400                                                                        
                                                                                    
layout(points) in;                                                                  
layout(triangle_strip) out;                                                         
layout(max_vertices = 4) out;                                                       
 
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;                                                                                   
uniform mat4 MVP;                                                                   
uniform vec3 gCameraPos;
uniform float width;  
uniform float height;               
uniform int column;
uniform int row;
uniform int num_column;
uniform int num_row;                                      
                                                                                    
out vec2 TexCoord;                                                                  
                                                                                    
void main()                                                                         
{                                                                                   
    vec3 Pos = gl_in[0].gl_Position.xyz;                                            
    vec3 toCamera = normalize(gCameraPos - Pos);                                    
    vec3 up = vec3(0.0, 1.0, 0.0);                                                  
    //vec3 right = cross(toCamera, up);            
	vec3 right = cross(toCamera, up) * width;    	
                                                                                    
    //Pos -= (right * 0.5);    
	Pos -= right/2.0;   
    Pos.y -= height/2.0;
    gl_Position = ProjectionMatrix * ViewMatrix * vec4(Pos, 1.0);                                             
    TexCoord = vec2(0.0, 0.0);                                                      
    EmitVertex();                                                                   
                                                                                    
    //Pos.y += 1.0;          
    Pos.y += height;   	
    gl_Position = ProjectionMatrix * ViewMatrix * vec4(Pos, 1.0);                                             
    TexCoord = vec2(0.0, 1.0);                                                      
    EmitVertex();                                                                   
                                                                                    
    //Pos.y -= 1.0;     
    Pos.y -= height;	
    Pos += right;                                                                   
    gl_Position = ProjectionMatrix * ViewMatrix * vec4(Pos, 1.0);                                             
    TexCoord = vec2(1.0, 0.0);                                                      
    EmitVertex();                                                                   
                                                                                    
    //Pos.y += 1.0;     
    Pos.y += height;    	
    gl_Position = ProjectionMatrix * ViewMatrix * vec4(Pos, 1.0);                                             
    TexCoord = vec2(1.0, 1.0);                                                      
    EmitVertex();                                                                   
                                                                                    
    EndPrimitive();                                                                 
}                                          