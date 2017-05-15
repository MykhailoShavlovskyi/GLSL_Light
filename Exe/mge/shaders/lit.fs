//DIFFUSE COLOR FRAGMENT SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

in vec4 fragWorldPosition;
in vec4 fragWorldNormal;

uniform vec3 diffuseColor;
uniform vec3 specularColor;

uniform int shininess;

uniform float pointLightCount;
uniform vec3 pointLightColor[5];
uniform vec3 pointLightPos[5];
uniform vec3 pointAttenuation[5];

uniform float directionalLightCount;
uniform vec3 directionalLightColor[5];
uniform vec3 directionalLightDir[5];

uniform float spotLightCount;
uniform vec3  spotLightColor[5];
uniform vec3  spotLightPos[5];
uniform vec3  spotLightDir[5];
uniform vec3  spotLightAttenuation[5];
uniform float  spotLightAngle[5];
uniform float  spotFallOffRate[5];

uniform vec4 cameraPosition;

out vec4 fragment_color;

vec4 lightDirectionNorm;
vec3 diffuseTerm;
vec3 specularTerm;

void main( void )
{
	//point lights
	for (int i = 0; i < pointLightCount; i ++)
	{
		lightDirectionNorm = normalize(fragWorldPosition - vec4(pointLightPos[i],1));
		
		float lightDistance = length (vec4(pointLightPos[i],1) - fragWorldPosition);
		float attenuationParameter = 1/(pointAttenuation[i].x + pointAttenuation[i].y * lightDistance + pointAttenuation[i].z * lightDistance * lightDistance );
		
		vec4 reflectedRay = lightDirectionNorm - 2*dot(lightDirectionNorm, fragWorldNormal)*fragWorldNormal;
		vec4 fragToCameraNorm = normalize(cameraPosition - fragWorldPosition);
		
		vec3 ambientTerm = vec3(0.2, 0.2, 0.2) * diffuseColor;
		diffuseTerm += max(dot(-lightDirectionNorm, fragWorldNormal),0) * pointLightColor[i] * diffuseColor * attenuationParameter;
		specularTerm += pow(max(dot(reflectedRay, fragToCameraNorm), 0), shininess) * pointLightColor[i] * specularColor * attenuationParameter;
		
	}
	
	//directional lights
	for (int i = 0; i < directionalLightCount; i ++)
	{
		lightDirectionNorm = normalize(vec4(directionalLightDir[i],0));
		
		vec4 reflectedRay = lightDirectionNorm - 2*dot(lightDirectionNorm, fragWorldNormal)*fragWorldNormal;
		vec4 fragToCameraNorm = normalize(cameraPosition - fragWorldPosition);
		
		diffuseTerm += max(dot(-lightDirectionNorm, fragWorldNormal),0) * directionalLightColor[i] * diffuseColor;
		specularTerm += pow(max(dot(reflectedRay, fragToCameraNorm),0), shininess) * directionalLightColor[i] * specularColor;
	}
	
	//spot lights
	for (int i = 0; i < spotLightCount; i ++)
	{
		lightDirectionNorm = normalize(fragWorldPosition - vec4(spotLightPos[i],1));
		float lightAngleRelativeToLightForward = acos(dot(lightDirectionNorm, vec4(spotLightDir[i],0)));
		
		if( lightAngleRelativeToLightForward < radians(spotLightAngle[i]))
		{
			float fallOffParameter = (min(radians(spotFallOffRate[i]), radians(spotLightAngle[i]) - lightAngleRelativeToLightForward))/radians(spotFallOffRate[i]);

			float lightDistance = length (vec4(spotLightPos[i],1) - fragWorldPosition);
			float attenuationParameter = 1/(spotLightAttenuation[i].x + spotLightAttenuation[i].y * lightDistance + spotLightAttenuation[i].z * lightDistance * lightDistance );
			
			
			vec4 reflectedRay = lightDirectionNorm - 2*dot(lightDirectionNorm, fragWorldNormal)*fragWorldNormal;
			vec4 fragToCameraNorm = normalize(cameraPosition - fragWorldPosition);
			
			vec3 ambientTerm = vec3(0.2, 0.2, 0.2) * diffuseColor;
			diffuseTerm += max(dot(-lightDirectionNorm, fragWorldNormal),0) * spotLightColor[i] * diffuseColor * attenuationParameter*fallOffParameter;
			specularTerm += pow(max(dot(reflectedRay, fragToCameraNorm), 0), shininess) * spotLightColor[i] * specularColor * attenuationParameter*fallOffParameter;
		}
	}
	fragment_color = vec4 (diffuseTerm+specularTerm,1);
}
