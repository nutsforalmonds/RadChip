#version 400

layout (location=0) out vec4 FragColor;

uniform vec3 color;
uniform sampler2D colorTex;
uniform int textureMeBaby;

in vec2 texCor;

void main()
{
	if(textureMeBaby == 0)
	{
		FragColor = vec4(color,1.0);
	}
	if(textureMeBaby == 1)
	{
		vec4 texColor = texture( colorTex, texCor );
		
		FragColor = texColor;
		
		if(FragColor.a<0.1)
		{
			discard;
		} 
	}
}