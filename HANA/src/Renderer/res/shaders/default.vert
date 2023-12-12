#version 330 core
layout (location = 0) in vec3 aPos;

// send color to frag shader
// out vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 orthographic;


void main()
{
	// gl_Position =  projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}