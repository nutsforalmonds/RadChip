#version 400
layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec2 VertexTexCoord;

uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;
uniform mat4 MVP;

out vec2 texCor;

void main()
{
	texCor = VertexTexCoord;
	gl_Position = ProjectionMatrix*ModelMatrix*vec4(VertexPosition,1.0);
}