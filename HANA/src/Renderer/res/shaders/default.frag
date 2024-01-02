#version 330 core

in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D image;
uniform vec3 Color; 

void main()
{
	FragColor = vec4(Color, 1.0) * texture(image, TexCoords);
	//FragColor = vec4(Color, 1.0);
}