//DIFFUSE COLOR FRAGMENT SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1
//in vec3 fColor;

in vec3 rotatedNormal;
in vec3 lightDirection;

uniform vec3 diffuseColor;
out vec4 fragment_color;



void main( void )
{
    float light = dot(rotatedNormal, lightDirection);
    light = (light+1)/2;

    vec3 color = diffuseColor;
    color = color * light ;

	fragment_color = vec4 (color,1);
}
