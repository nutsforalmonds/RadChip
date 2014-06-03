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
out vec3 world_pos;
flat out vec3 world_cam;                                                    
                                                                                    
void main()                                                                         
{
    world_cam = (inverse(ViewMatrix)*vec4(0,0,0,1)).xyz;                                               

	float seg_width = 1.0/num_column;
	float seg_height = 1.0/num_row;
	float a = column*seg_width;
	float b = 1-row*seg_height;

    vec3 Pos = gl_in[0].gl_Position.xyz;                                            
    vec3 toCamera = normalize(gCameraPos - Pos);                                    
    vec3 up = vec3(0.0, 1.0, 0.0);                                                  
    //vec3 right = cross(toCamera, up);            
	vec3 right = normalize(cross(toCamera, up)) * width;    	
                                                                                    
    //Pos -= (right * 0.5);    
	Pos -= right/2.0;   
    Pos.y -= height/2.0;
    gl_Position = ProjectionMatrix * ViewMatrix * vec4(Pos, 1.0);                                             
    TexCoord = vec2(a, b-seg_height);                             
    world_pos = Pos;                   
    EmitVertex();                                                                   
                                                                                    
    //Pos.y += 1.0;          
    Pos.y += height;   	
    gl_Position = ProjectionMatrix * ViewMatrix * vec4(Pos, 1.0);                                             
    TexCoord = vec2(a, b);     
    world_pos = Pos;                                                    
    EmitVertex();                                                                   
                                                                                    
    //Pos.y -= 1.0;     
    Pos.y -= height;	
    Pos += right;                                                                   
    gl_Position = ProjectionMatrix * ViewMatrix * vec4(Pos, 1.0);                                             
    TexCoord = vec2(a+seg_width, b-seg_height);  
    world_pos = Pos;                                                       
    EmitVertex();                                                                   
                                                                                    
    //Pos.y += 1.0;     
    Pos.y += height;    	
    gl_Position = ProjectionMatrix * ViewMatrix * vec4(Pos, 1.0);                                             
    TexCoord = vec2(a+seg_width, b);          
    world_pos = Pos;                                               
    EmitVertex();                                                                   
                                                                                    
    EndPrimitive();                                                                 
}                                          