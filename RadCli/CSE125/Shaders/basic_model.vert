#version 400


const int MAX_BONES = 100;

uniform	mat4 projMatrix;
uniform	mat4 viewMatrix;
uniform	mat4 modelMatrix;
uniform mat4 gBones[MAX_BONES];

layout (location = 0) in vec3 Position;                                             
layout (location = 1) in vec2 TexCoordd;                                             
layout (location = 2) in vec3 normal;                                               
layout (location = 3) in ivec4 BoneIDs;
layout (location = 4) in vec4 Weights;

out vec4 vertexPos;
out vec2 TexCoord;
out vec3 Normal;

void main()
{
	mat4 BoneTransform = gBones[BoneIDs[0]] * Weights[0];
	BoneTransform     += gBones[BoneIDs[1]] * Weights[1];
	BoneTransform     += gBones[BoneIDs[2]] * Weights[2];
    BoneTransform     += gBones[BoneIDs[3]] * Weights[3];
    vec4 PosL    = BoneTransform * vec4(Position, 1.0);
	vec4 NormalL = BoneTransform * vec4(normal, 0.0);

    gl_Position = projMatrix*viewMatrix*modelMatrix*PosL;
    Normal = (modelMatrix*NormalL).xyz;
    vertexPos = modelMatrix*PosL;
    TexCoord = TexCoordd;
}