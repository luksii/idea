#version 330 core

in vec3 ourColor;
in vec2 TexCoord;
//in vec3 offsetColor;

uniform sampler2D ourTexture;

out vec4 FragColor;

void main()
{
	FragColor = texture(ourTexture, TexCoord);
	//FragColor = vec4(ourColor, 1.0);
}