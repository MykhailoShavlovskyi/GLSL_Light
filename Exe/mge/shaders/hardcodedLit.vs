//DIFFUSE COLOR VERTEX SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

in vec3 vertex;
in vec3 normal;
in vec2 uv;

uniform	mat4    mvpMatrix;


out vec3 rotatedNormal;
out vec3 lightDirection;

void main( void )
{
	gl_Position = mvpMatrix * vec4(vertex, 1.f);

	vec3 lighPoint = vec3(0,5,0);
    lightDirection = normalize( lighPoint - vec3(gl_Position));

	mat4 rotationMat = mat4(mvpMatrix[0],mvpMatrix[1],mvpMatrix[2],vec4(0,0,0,1));
    rotatedNormal = vec3(rotationMat * vec4(normal, 1.f));
}
