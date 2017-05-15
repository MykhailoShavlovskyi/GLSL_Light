//DIFFUSE COLOR VERTEX SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1
in vec3 vertex;
in vec3 normal;
in vec2 uv;

uniform	mat4 mvpMatrix;
uniform	mat4 modelMatrix;

out vec4 fragWorldPosition;
out vec4 fragWorldNormal;

void main( void )
{
	gl_Position = mvpMatrix * vec4(vertex, 1.f);

	fragWorldPosition = modelMatrix * vec4 (vertex, 1);
	fragWorldNormal= normalize (modelMatrix * vec4 (normal, 0));
}
