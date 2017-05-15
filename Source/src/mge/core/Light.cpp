#include "mge/core/Light.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/config.hpp"

Light::Light(std::string pName, glm::vec3 pPosition, glm::vec3 lightColor, Type type, glm::vec3 pAttenuation)
:	GameObject(pName, pPosition)
{
    _lightColor = lightColor;
    _type = type;
	_attenuation = pAttenuation;

	//setup models
	model = new GameObject("light_model", glm::vec3(0,0,0));
	_pointMesh = Mesh::load(config::MGE_MODEL_PATH + "sphere_smooth.obj");
	_directionalMesh = Mesh::load(config::MGE_MODEL_PATH + "cone_flat.obj");

	switch (_type)
	{
	case Type::POINT:
		model->setMesh(_pointMesh);
		model->scale(glm::vec3(.4f, .4f, .4f));
		break;
	case Type::DIRRECTIONAL:
		model->setMesh(_directionalMesh);
		model->scale(glm::vec3(.5f, .5f, .5f));
		break;
	case Type::SPOT:
		model->setMesh(_directionalMesh);
		model->scale(glm::vec3(.5f, .2f, .5f));
		break;
	}

	model->setMaterial(new ColorMaterial(lightColor));
	model->setParent(this);
	model->rotate(glm::radians(90.), glm::vec3(1, 0, 0));
	
	//add keys beahviour
	setBehaviour(new KeysBehaviour());
}

Light::~Light()
{
    //dtor             
}

void Light::setColor(glm::vec3 newColor)
{
	_lightColor = newColor;
	model->setMaterial(new ColorMaterial(_lightColor));
}

void Light::setAttenuation(glm::vec3 newAttenuation)
{
	if (newAttenuation.x >= 1, newAttenuation.y >= 0, newAttenuation.z >= 0)
	{
		_attenuation = newAttenuation;
	}
	else
	{
		std::cout << "invalid inout attenuation";
	}
}

void Light::setAngle(float newAngle)
{
	_angle = newAngle;
}

void Light::setFallOffRate(float newFallOffRate)
{
	_fallOffRate = newFallOffRate;
}

void Light::changeType(Type newType)
{
	if (newType != _type)
	{
		LightUtil::RemoveLight(this);

		switch (_type)
		{
		case Type::POINT:
			model->scale(glm::vec3(2.5, 2.5, 2.5));
			break;
		case Type::DIRRECTIONAL:
			model->scale(glm::vec3(2, 2, 2));
			break;
		case Type::SPOT:
			model->scale(glm::vec3(2, 5, 2));
			break;
		}

		_type = newType;

		switch (_type)
		{
		case Type::POINT:
			model->setMesh(_pointMesh);
			model->scale(glm::vec3(.4f, .4f, .4f));
			break;
		case Type::DIRRECTIONAL:
			model->setMesh(_directionalMesh);
			model->scale(glm::vec3(.5f, .5f, .5f));
			break;
		case Type::SPOT:
			model->setMesh(_directionalMesh);
			model->scale(glm::vec3(.5f, .2f, .5f));
			break;
		}

		LightUtil::AddLight(this);
	}
}
