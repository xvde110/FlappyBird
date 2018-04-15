#version 410 core

out vec4 color;

in vec2 TexCoord;

uniform sampler2D img;

void main()
{
	color=texture(img,TexCoord);
}