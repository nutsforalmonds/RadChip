#version 400

const int MAX_BONES = 100;

layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec2 VertexTexCoord;
layout (location=2) in vec3 VertexNormal;
layout (location=3) in ivec4 BoneIDs1;
layout (location=4) in ivec4 BoneIDs2;
layout (location=5) in vec4 Weights1;
layout (location=6) in vec4 Weights2;
layout (location=7) in int BoneCount;

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
	mat4 BoneTransform = mat4(0.0);

	for(int i=0; i<BoneCount; i++){
		if(i<4 ){
			BoneTransform += gBones[BoneIDs1[i]] * Weights1[i];
		}else{
			BoneTransform += gBones[BoneIDs2[i%4]] * Weights2[i%4];
		}
	}

	if(BoneTransform == mat4(0.0)){
		BoneTransform[3][3] = 1.0;
	}

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