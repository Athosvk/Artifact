#version 130

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUVCoordinate;

out vec4 color;

uniform float angle;
uniform sampler2D sampler;

const vec4 Sepia = vec4(1.2, 1.0, 0.8, 1);

void main() 
{
	vec4 resultingColor = texture(sampler, fragmentUVCoordinate) * fragmentColor;
	float greyScale = (resultingColor.r + resultingColor.g + resultingColor.b) / 3;
	vec4 sepia = vec4(greyScale, greyScale, greyScale, 1) * Sepia;
	color = mix(sepia, resultingColor, 1);
}
