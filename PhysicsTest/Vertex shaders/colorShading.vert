#version 130

in vec2 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUVCoordinate;

out vec4 fragmentColor;
out vec2 fragmentUVCoordinate;

uniform float time;

uniform mat4 cameraTransform;

void main()
{	
	vec4 transformedPosition =  cameraTransform * vec4(vertexPosition, 0, 1);
	gl_Position = transformedPosition;
	
	fragmentColor = vertexColor;
    fragmentUVCoordinate = vec2(vertexUVCoordinate.x, 1.0 - vertexUVCoordinate.y);
}