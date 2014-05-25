#version 400   

layout (location=0) in float aTheta;
layout (location=1) in vec3 aShade;

// Uniforms
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix; 
uniform float uK;
uniform float uTime;
 
//out vec3 position;//position in world
out vec3 vShade;

void main(void)
{
    float x = uTime * cos(uK*aTheta)*sin(aTheta);
    float y = uTime * cos(uK*aTheta)*cos(aTheta);
	
	//float x = uTime * cos(aTheta);
    //float y = uTime * sin(aTheta);
	
	vec4 position = vec4(x, y, 0.0, 1.0);

    //gl_Position = ProjectionMatrix*ViewMatrix*ModelMatrix*position;
	gl_Position = position;
    gl_PointSize = 25.0;
	
	//position = vec3(ModelMatrix*vec4(x, y, 0.0,1.0));
	
	vShade = aShade;
}     