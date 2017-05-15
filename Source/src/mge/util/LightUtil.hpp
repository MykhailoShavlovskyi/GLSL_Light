#ifndef LIGHTUTIL_Def
#define LIGHTUTIL_Def

class Camera;
class Light;

#include <glm.hpp>
#include <vector>

class LightUtil
{
public:
	static void AddLight(Light* pLight);
	static void RemoveLight(Light* pLight);

	static int GetPointLigthsCount();
	static std::vector<glm::vec3> GetPointLigthsPositions();
	static std::vector<glm::vec3> GetPointLigthsColors();
	static std::vector<glm::vec3> GetPointLigthsAttenuations();

	static int GetDirectionalLigthsCount();
	static std::vector<glm::vec3> GetDirectionalLigthsColors();
	static std::vector<glm::vec3> GetDirectionalLigthsDirections();

	static int GetSpotLigthsCount();
	static std::vector<glm::vec3> GetSpotLigthsPositions();
	static std::vector<glm::vec3> GetSpotLigthsColors();
	static std::vector<glm::vec3> GetSpotLigthsDirections();
	static std::vector<glm::vec3> GetSpotLigthsAttenuations();
	static std::vector<float> GetSpotLigthsAngles();
	static std::vector<float> GetSpotLigthsFallOffRates();
};

#endif