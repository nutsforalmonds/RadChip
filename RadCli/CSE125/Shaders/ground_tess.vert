#version 400
layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec3 VertexNormal;
layout (location=2) in vec2 VertexTexCoord;

uniform mat4 ModelMatrix;

out vec3 WorldPos_CS_in;                                                                        
out vec2 TexCoord_CS_in;                                                                        

void main()
{

	WorldPos_CS_in = vec3(ModelMatrix*vec4(VertexPosition,1.0));
	TexCoord_CS_in = VertexTexCoord;
}