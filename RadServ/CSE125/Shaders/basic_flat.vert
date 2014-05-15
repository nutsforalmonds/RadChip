#version 400
layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec3 VertexNormal;

uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;
uniform mat4 MVP;

void main()
{
	gl_Position = ProjectionMatrix*ModelMatrix*vec4(VertexPosition,1.0);
}