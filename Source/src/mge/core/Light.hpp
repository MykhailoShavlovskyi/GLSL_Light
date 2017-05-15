#ifndef LIGHT_H
#define LIGHT_H

using namespace std;

#include "mge/core/GameObject.hpp"
#include "mge/util/LightUtil.hpp"
#include <iostream>
#include <glm.hpp>

class Mesh;



class Light : public GameObject
{
    public:
		static enum Type { POINT, DIRRECTIONAL, SPOT };

        Light(std::string pName, glm::vec3 pPosition, glm::vec3 lightColor, Type type, glm::vec3 pAttenuation);
        virtual ~Light();

		Type _type;
        glm::vec3 _lightColor;
		glm::vec3 _attenuation;
		float _angle = 30;
		float _fallOffRate = 10;
		GameObject * model;

		void setColor(glm::vec3 newColor);
		void setAttenuation(glm::vec3 newAttenuation);
		void setAngle(float newAngle);
		void setFallOffRate(float newFallOffRate);
		void changeType(Type newType);

	private:
		Mesh * _pointMesh;
		Mesh * _directionalMesh;
};

#endif // LIGHT_H
