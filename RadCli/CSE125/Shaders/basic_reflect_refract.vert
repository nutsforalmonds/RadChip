#version 400
layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec3 VertexNormal;

uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;
uniform mat4 MVP;

uniform mat4 LightView;
uniform mat4 LightProjection;
uniform mat4 ScaleBias;
out vec3 shadow_coord;

out vec3 position;//position in world
out vec3 normal;//normal in world
flat out vec3 cam;//camera in world

void main()
{
	gl_Position = MVP*vec4(VertexPosition,1.0);

	normal = vec3(ModelMatrix*vec4(VertexNormal,0));
	position = vec3(ModelMatrix*vec4(VertexPosition,1.0));
	cam = vec3(inverse(ViewMatrix)*vec4(0,0,0,1));

	vec4 lightCoord = LightProjection*LightView*vec4(position,1.0);
	lightCoord = lightCoord/lightCoord.w;
	lightCoord = ScaleBias*lightCoord;
	shadow_coord = vec3(lightCoord.x,lightCoord.y,lightCoord.z);
}