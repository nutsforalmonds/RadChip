#version 400

layout (location=0) out vec4 FragColor;

uniform vec3 color;
uniform sampler2D myTexture;

in vec2 texCor;

void main()
{
	FragColor = vec4(color,1.0);
	//FragColor = texture2D(myTexture, texCor).bgra;
}