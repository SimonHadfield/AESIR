#version 330 core
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;
layout (location = 1) in vec2 aTex;

// send color to frag shader
out vec3 color;
// send texCoordinates to frag shader
out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
	//projection * view * model *
	gl_Position =  model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	//color = aColor;
	texCoord = aTex;
}