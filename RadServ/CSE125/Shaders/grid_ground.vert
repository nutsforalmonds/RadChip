#version 400
layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec3 VertexNormal;
layout (location=2) in vec2 VertexTexCoord;

uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;
uniform mat4 MVP;
uniform mat4 LightView;
uniform mat4 LightProjection;
uniform mat4 ScaleBias;

uniform float dispHeight;

uniform	sampler2D displacementTex;
//uniform sampler2D normalTex;

out vec3 position;//position in world
//out vec3 normal;//normal in world
out vec2 texCor;
flat out vec3 cam;//camera in world

out vec3 shadow_coord;

void main()
{
	vec4 disp = texture(displacementTex, VertexTexCoord);
	//vec4 norm = texture(normalTex, VertexTexCoord);

	gl_Position = MVP*vec4(VertexPosition+vec3(0,disp[0]*dispHeight,0),1.0);

	//normal = vec3(ModelMatrix*vec4(2*vec3(norm[1],norm[2],norm[0])-vec3(1.0,1.0,1.0),0));//normal = vec3(ModelMatrix*vec4(VertexNormal,0));
	position = vec3(ModelMatrix*vec4(VertexPosition+vec3(0,disp[0]*dispHeight,0),1.0));
	cam = vec3(inverse(ViewMatrix)*vec4(0,0,0,1));
	texCor = VertexTexCoord;

	vec4 lightCoord = LightProjection*LightView*vec4(VertexPosition+vec3(0,disp[0]*dispHeight,0),1.0);
	lightCoord = lightCoord/lightCoord.w;
	lightCoord = ScaleBias*lightCoord;
	shadow_coord = vec3(lightCoord.x,lightCoord.y,lightCoord.z);
}