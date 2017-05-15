#include "mge/util/LightUtil.hpp"
#include <mge/core/Light.hpp>;

static std::vector <Light*> _pointLights;
static std::vector <Light*> _directionalLights;
static std::vector <Light*> _spotLights;

void LightUtil::AddLight(Light* pLight)
{
	switch (pLight->_type)
	{
	case Light::Type::POINT:
		_pointLights.push_back(pLight);
		break;
	case Light::Type::DIRRECTIONAL:
		_directionalLights.push_back(pLight);
		break;
	case Light::Type::SPOT:
		_spotLights.push_back(pLight);
		break;
	}
}

void LightUtil::RemoveLight(Light* pLight)
{
	switch (pLight->_type)
	{
	case Light::Type::POINT:
		for (int i = 0, size = _pointLights.size(); i < size; i++)
		{
			if (_pointLights[i] == pLight)
			{
				_pointLights.erase(_pointLights.begin() + i);
				return;
			}
		}
		break;
	case Light::Type::DIRRECTIONAL:
		for (int i = 0, size = _directionalLights.size(); i < size; i++)
		{
			if (_directionalLights[i] == pLight)
			{
				_directionalLights.erase(_directionalLights.begin() + i);
				return;
			}
		}
		break;
	case Light::Type::SPOT:
		for (int i = 0, size = _spotLights.size(); i < size; i++)
		{
			if (_spotLights[i] == pLight)
			{
				_spotLights.erase(_spotLights.begin() + i);
				return;
			}
		}
		break;
	}
}

//-------------------------------POINT LIGHTS-----------------------------------------
int LightUtil::GetPointLigthsCount()
{
	return _pointLights.size();
}
std::vector<glm::vec3> LightUtil::GetPointLigthsPositions()
{
	std::vector<glm::vec3> positions;
	for (int i = 0; i < _pointLights.size(); i++)
	{
		positions.push_back(_pointLights[i]->getWorldPosition());
	}
	return positions;
}
std::vector<glm::vec3> LightUtil::GetPointLigthsColors()
{
	std::vector<glm::vec3> colors;
	for (int i = 0; i < _pointLights.size(); i++)
	{
		colors.push_back(_pointLights[i]->_lightColor);
	}
	return colors;
}
std::vector<glm::vec3> LightUtil::GetPointLigthsAttenuations()
{
	std::vector<glm::vec3> attenuations;
	for (int i = 0; i < _pointLights.size(); i++)
	{
		attenuations.push_back(_pointLights[i]->_attenuation);
	}
	return attenuations;
}
//-------------------------------DIRECTIONAL LIGHTS-----------------------------------------
int LightUtil::GetDirectionalLigthsCount()
{
	return _directionalLights.size();
}
std::vector<glm::vec3> LightUtil::GetDirectionalLigthsColors()
{
	std::vector<glm::vec3> colors;
	for (int i = 0; i < _directionalLights.size(); i++)
	{
		colors.push_back(_directionalLights[i]->_lightColor);
	}
	return colors;
}
std::vector<glm::vec3> LightUtil::GetDirectionalLigthsDirections()
{
	std::vector<glm::vec3> directions;
	for (int i = 0; i < _directionalLights.size(); i++)
	{
		directions.push_back(_directionalLights[i]->getTransform()[2]);
	}
	return directions;
}
//-------------------------------SPOT LIGHTS-----------------------------------------
int LightUtil::GetSpotLigthsCount()
{
	return _spotLights.size();
}
std::vector<glm::vec3> LightUtil::GetSpotLigthsPositions()
{
	std::vector<glm::vec3> positions;
	for (int i = 0; i < _spotLights.size(); i++)
	{
		positions.push_back(_spotLights[i]->getWorldPosition());
	}
	return positions;
}
std::vector<glm::vec3> LightUtil::GetSpotLigthsColors()
{
	std::vector<glm::vec3> colors;
	for (int i = 0; i < _spotLights.size(); i++)
	{
		colors.push_back(_spotLights[i]->_lightColor);
	}
	return colors;
}
std::vector<glm::vec3> LightUtil::GetSpotLigthsDirections()
{
	std::vector<glm::vec3> directions;
	for (int i = 0; i < _spotLights.size(); i++)
	{
		directions.push_back(_spotLights[i]->getTransform()[2]);
	}
	return directions;
}
std::vector<glm::vec3> LightUtil::GetSpotLigthsAttenuations()
{
	std::vector<glm::vec3> attenuations;
	for (int i = 0; i < _spotLights.size(); i++)
	{
		attenuations.push_back(_spotLights[i]->_attenuation);
	}
	return attenuations;
}
std::vector<float> LightUtil::GetSpotLigthsAngles()
{
	std::vector<float> angles;
	for (int i = 0; i < _spotLights.size(); i++)
	{
		angles.push_back(_spotLights[i]->_angle);
	}
	return angles;
}
std::vector<float> LightUtil::GetSpotLigthsFallOffRates()
{
	std::vector<float> fallOffRates;
	for (int i = 0; i < _spotLights.size(); i++)
	{
		fallOffRates.push_back(_spotLights[i]->_fallOffRate);
	}
	return fallOffRates;
}

