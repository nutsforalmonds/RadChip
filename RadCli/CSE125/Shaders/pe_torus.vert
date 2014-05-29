#version 400   

// Attributes
layout (location=0) in float a_pID;
layout (location=1) in float a_pID2;
layout (location=2) in float a_pRadiusOffset;
layout (location=3) in float a_pVelocityOffset;
layout (location=4) in float a_pDecayOffset;
layout (location=5) in float a_pSizeOffset;
layout (location=6) in vec3 a_pColorOffset;

// Uniforms
uniform mat4	u_ViewMatrix;
uniform mat4	u_ProjectionMatrix;
uniform mat4	u_ModelMatrix; 
uniform vec2	u_Gravity;
uniform float   u_Time;
uniform float   u_eRadius;
uniform float   u_eVelocity;
uniform float   u_eDecay;
uniform float   u_eSizeStart;
uniform float   u_eSizeEnd;
uniform vec3	u_ePosition;

// Varying
out vec3		v_pColorOffset;
out float		v_Growth;
out float		v_Decay;

out vec3 position;//position in world
flat out vec3 cam;//camera in world

void main(void)
{
	// Convert polar angle to cartesian coordinates and calculate radius
	//float x = cos(a_pID);
	//float y = sin(a_pID);
	//float r = u_eRadius * a_pRadiusOffset;

	//Convert Spherical angles to cartesian coordinates and calculate radius
	//float x = sin(a_pID2)*cos(a_pID);
	//float y = sin(a_pID2)*sin(a_pID);
	//float z = cos(a_pID2);
	//float r = u_eRadius * a_pRadiusOffset;
	
	float c = 1.0;
	float a = 0.5;

	float x = ((c + (a*cos(a_pID2)))*cos(a_pID));
	float y = ((c + (a*cos(a_pID2)))*sin(a_pID));
	float z = (a*sin(a_pID2));
	float r = u_eRadius * a_pRadiusOffset;

	// Lifetime
	float growth = r / (u_eVelocity + a_pVelocityOffset);
	float decay = u_eDecay + a_pDecayOffset;

	// Size
    float s = 1.0;

	// If blast is growing
	if(u_Time < growth)
	{
		float time = u_Time / growth;
		x = x * r * time;
		y = y * r * time;
		z = z * r * time;
		s = u_eSizeStart;
	}

	// Else if blast is decaying
	else
	{
		float time = (u_Time - growth) / decay;
		x = (x * r) + (u_Gravity.x * time);
		y = (y * r) + (u_Gravity.y * time);
		z = (z * r) + (u_Gravity.x * time);

		s = mix(u_eSizeStart, u_eSizeEnd, time);
	}

	
	//Outputs
	//vec3 tempPos = vec3(x, y, 0.0) + u_ePosition;
	vec3 tempPos = vec3(x, y, z) + u_ePosition;
	vec4 pos = vec4(tempPos, 1.0);

	cam = vec3(inverse(u_ViewMatrix)*vec4(0,0,0,1));
	position = vec3(u_ModelMatrix*pos);
	
	gl_Position = u_ProjectionMatrix*u_ViewMatrix*u_ModelMatrix*pos;
	
	gl_PointSize = max(0.0, (s + a_pSizeOffset));
 
	// Fragment Shader outputs
	v_pColorOffset = a_pColorOffset;
	v_Growth = growth;
    v_Decay = decay;
}                                                                         
