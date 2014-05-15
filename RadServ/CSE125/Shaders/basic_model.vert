#version 400

const int MAX_BONES = 100;

layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec2 VertexTexCoord;
layout (location=2) in vec3 VertexNormal;
layout (location = 3) in ivec4 BoneIDs;
layout (location = 4) in vec4 Weights;

uniform	mat4 Model;
uniform	mat4 View;
uniform	mat4 Projection;
uniform mat4 gBones[MAX_BONES];

uniform mat4 LightView;
uniform mat4 LightProjection;
uniform mat4 ScaleBias;
out vec3 shadow_coord;

out vec3 position;//position in world
out vec3 normal;//normal in world
out vec2 texCoord;//texture coordinate
flat out vec3 cam;//camera in world

void main()
{
	mat4 BoneTransform = gBones[BoneIDs[0]] * Weights[0];
	BoneTransform     += gBones[BoneIDs[1]] * Weights[1];
	BoneTransform     += gBones[BoneIDs[2]] * Weights[2];
    BoneTransform     += gBones[BoneIDs[3]] * Weights[3];
    vec4 PosL    = BoneTransform * vec4(VertexPosition, 1.0);
	vec4 NormalL = BoneTransform * vec4(VertexNormal, 0.0);

	gl_Position = Projection*View*Model*PosL;

	normal = (Model*NormalL).xyz;
	position = (Model*PosL).xyz;
	texCoord = VertexTexCoord;
	cam = (inverse(View)*vec4(0,0,0,1)).xyz;

	// uncomment to enable shadow 
	// vec4 lightCoord = LightProjection*LightView*vec4(position,1.0);
	// lightCoord = lightCoord/lightCoord.w;
	// lightCoord = ScaleBias*lightCoord;
	// shadow_coord = vec3(lightCoord.x,lightCoord.y,lightCoord.z);
}