#version 130

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 uvFragmentCoordinate;

out vec4 color;

uniform float angle;

float getAngle(vec2 a_Vector);

void main() 
{
	if (angle > degrees(getAngle(fragmentPosition)) + 180)
	{
		color = fragmentColor;
	}
	else
	{
		color = vec4(0.0, 0.0, 0.0, 0.0);
	}
}

float getAngle(vec2 a_Vector)
{
	return atan(a_Vector.y, a_Vector.x);
}
