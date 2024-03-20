#version 330 core

out vec4 FragColor;

in vec3 color;

//vec4 color = vec4(0.0, 0.0, 0.0, 1.0);

void main()
{
	FragColor = vec4(color, 1.0);
}