#version 400   

layout (location=0) in float aTheta;
layout (location=1) in vec3 aShade;

// Uniforms
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix; 
uniform float uK;
uniform float uTime;

out vec3 vShade;
out vec3 position;//position in world
flat out vec3 cam;//camera in world

void main(void)
{
    //float x = uTime * cos(uK*aTheta)*sin(uK*aTheta);
    //float y = uTime * cos(uK*aTheta)*cos(uK*aTheta);
	//float z = 0.0;

	//Convert Spherical angles to cartesian coordinates and calculate radius
	float x = uTime * cos(aTheta);
	float y = uTime * sin(aTheta);
	float z = uTime;

	
	//float x = cos(aTheta);
    //float y = sin(aTheta);

	vec4 pos = vec4(x, y, z, 1.0);

	position = vec3(ModelMatrix*pos);
	cam = vec3(inverse(ViewMatrix)*vec4(0,0,0,1));

    gl_Position = ProjectionMatrix*ViewMatrix*ModelMatrix*pos;
	//gl_Position = position;
    gl_PointSize = (25.0 / uTime);
	
	//position = vec3(ModelMatrix*vec4(x, y, 0.0,1.0));
	
	vShade = aShade;
}                                                                         
