#version 330 core

out vec4 FragColor;

in vec3 fragColor;
in vec2 texCoord;

uniform sampler2D tex0;

void main()
{
	FragColor = vec3(1.0,1.0,1.0);
	//vec4 textureColor = texture(tex0, texCoord);
	//FragColor = vec4(textureColor.rgb * fragColor, textureColor.a);
}