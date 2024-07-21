#version 330 core

in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D image;
uniform vec3 Color; 

void main()
{
	//FragColor = texture(image, TexCoords); //+ vec4(Color*vec3(0.5), 1.0);
	FragColor = texture(image, TexCoords);
}