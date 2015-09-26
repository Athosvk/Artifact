#version 130

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUVCoordinate;

out vec4 color;

uniform float angle;
uniform sampler2D sampler;

void main() 
{
	vec4 resultingColor = texture(sampler, fragmentUVCoordinate);
	float greyScale = (resultingColor.r + resultingColor.g + resultingColor.b) / 3;
	color.r = greyScale;
	color.g = greyScale;
	color.b = greyScale;
}
