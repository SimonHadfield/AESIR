#version 330 core
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;
layout (location = 1) in vec2 aTex;

// send color to frag shader
out vec3 fragColor;
// send texCoordinates to frag shader
out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
//uniform mat4 orthographic;


void main()
{
	gl_Position =  projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	//gl_Position = orthographic * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	fragColor = vec3(1.0, 1.0, 1.0);  // white color
	texCoord = aTex;
}