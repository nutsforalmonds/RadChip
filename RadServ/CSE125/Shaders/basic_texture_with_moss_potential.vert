#version 400
layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec3 VertexNormal;
layout (location=2) in vec2 VertexTexCoord;

uniform	mat4 Model;
uniform	mat4 View;
uniform	mat4 Projection;

out vec3 position;//position in world
out vec3 normal;//normal in world
out vec2 texCoord;//texture coordinate
flat out vec3 cam;//camera in world

void main()
{
	gl_Position = Projection*View*Model*vec4(VertexPosition,1.0);

	normal = (Model*vec4(VertexNormal,0.0)).xyz;
	position = (Model*vec4(VertexPosition,1.0)).xyz;
	texCoord = VertexTexCoord;
	cam = (inverse(View)*vec4(0,0,0,1)).xyz;
}