#version 130

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUVCoordinate;

out vec4 color;

uniform sampler2D sampler;

void main() 
{
	color = texture(sampler, fragmentUVCoordinate) * fragmentColor;
}
