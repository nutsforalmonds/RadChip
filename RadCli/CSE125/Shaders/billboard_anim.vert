#version 400                                                                        
                                                                                    
layout (location=0) in vec3 VertexPosition;

uniform mat4 ModelMatrix;
//uniform mat4 MVP;         

out vec3 position;//position in world
//flat out vec3 cam;//camera in world                             
                                                                                    
void main()                                                                         
{                                                                                     
	//gl_Position = MVP*vec4(VertexPosition,1.0);
	gl_Position = ModelMatrix*vec4(VertexPosition,1.0);

	//position = vec3(ModelMatrix*vec4(VertexPosition,1.0));
	//cam = vec3(inverse(ViewMatrix)*vec4(0,0,0,1));
}                                                                                    
