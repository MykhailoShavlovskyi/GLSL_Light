#include <glm.hpp>
#include "mge/materials/LitMaterial.hpp"
#include "mge/config.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include <SFML/Window/Keyboard.hpp>
#include "mge/util/LightUtil.hpp"

ShaderProgram* LitMaterial::_shader = NULL;

//vertex shader
GLint LitMaterial::_aVertex = 0;
GLint LitMaterial::_aNormal = 0;
GLint LitMaterial::_aUV = 0;
GLint LitMaterial::_uMVPMatrix = 0;
GLint LitMaterial::_uModelMatrix = 0;

//fragment shader
GLint LitMaterial::_uDiffuseColor = 0;
GLint LitMaterial::_uSpecularColor = 0;
GLint LitMaterial::_uShininess = 0;

GLint LitMaterial::_uPointLightCount = 0;
GLint LitMaterial::_uPointLightColor = 0;
GLint LitMaterial::_uPointLightPos = 0;
GLint LitMaterial::_uPointAttenuation = 0;

GLint LitMaterial::_uDirectionalLightCount = 0;
GLint LitMaterial::_uDirectionalLightColor = 0;
GLint LitMaterial::_uDirectionalLightDir = 0;

GLint LitMaterial::_uSpotLightCount = 0;
GLint LitMaterial::_uSpotLightColor = 0;
GLint LitMaterial::_uSpotLightPos = 0;
GLint LitMaterial::_uSpotLightDir = 0;
GLint LitMaterial::_uSpotLightAttenuation = 0;
GLint LitMaterial::_uSpotLightAngle = 0;
GLint LitMaterial::_uFallOffRate = 0;

GLint LitMaterial::_uCameraPosition = 0;

LitMaterial::LitMaterial(glm::vec3 pDiffuseColor, glm::vec3 pSpecularColor, int pShininess, Camera * pCamera):
	_diffuseColor (pDiffuseColor), _specularColor(pSpecularColor), _shininess(pShininess), _camera(pCamera)
{
    _lazyInitializeShader();
}

void LitMaterial::_lazyInitializeShader()
{
    if (!_shader) 
	{
		//add shader
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"lit.vs");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"lit.fs");
        _shader->finalize();

        //cache all uniform and attribute indexes of VERTEX shader
		_aVertex = _shader->getAttribLocation("vertex");
		_aNormal = _shader->getAttribLocation("normal");
		_aUV = _shader->getAttribLocation("uv");
        _uMVPMatrix= _shader->getUniformLocation("mvpMatrix");
		_uModelMatrix = _shader->getUniformLocation("modelMatrix");
		
		//cache all uniform and attribute indexes of FRAGMENT shader
        _uDiffuseColor = _shader->getUniformLocation("diffuseColor");
		_uSpecularColor = _shader->getUniformLocation("specularColor");
		_uShininess = _shader->getUniformLocation("shininess");

		_uPointLightCount = _shader->getUniformLocation("pointLightCount");
        _uPointLightColor = _shader->getUniformLocation("pointLightColor");
		_uPointLightPos = _shader->getUniformLocation("pointLightPos");
		_uPointAttenuation = _shader->getUniformLocation("pointAttenuation");

		_uDirectionalLightCount = _shader->getUniformLocation("directionalLightCount");
		_uDirectionalLightColor = _shader->getUniformLocation("directionalLightColor");
		_uDirectionalLightDir = _shader->getUniformLocation("directionalLightDir");

		_uSpotLightCount = _shader->getUniformLocation("spotLightCount");
		_uSpotLightColor = _shader->getUniformLocation("spotLightColor");
		_uSpotLightPos = _shader->getUniformLocation("spotLightPos");
		_uSpotLightDir = _shader->getUniformLocation("spotLightDir");
		_uSpotLightAttenuation = _shader->getUniformLocation("spotLightAttenuation");
		_uSpotLightAngle = _shader->getUniformLocation("spotLightAngle");
		_uFallOffRate = _shader->getUniformLocation("spotFallOffRate");

		_uCameraPosition = _shader->getUniformLocation("cameraPosition");
    }
}

LitMaterial::~LitMaterial()
{
    //dtor
}

void LitMaterial::render(Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix)
{
    _shader->use();

	//send model info
    glm::mat4 mvpMatrix = pProjectionMatrix * pViewMatrix * pModelMatrix;
    glUniformMatrix4fv ( _uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix)); //mvp matrix
	glUniformMatrix4fv(_uModelMatrix, 1, GL_FALSE, glm::value_ptr(pModelMatrix)); //model matrix
	pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV); //vertecies, normals, uvs

	//send material info
	glUniform3fv(_uDiffuseColor, 1, glm::value_ptr(_diffuseColor)); //diffuse color
	glUniform3fv(_uSpecularColor, 1, glm::value_ptr(_specularColor)); //specular color
	glUniform1i(_uShininess, _shininess); //shininess

	//send point lights data
	int pointLightCount = LightUtil::GetPointLigthsCount();
	glUniform1f(_uPointLightCount, pointLightCount); //point light count
	glUniform3fv(_uPointLightColor, pointLightCount, glm::value_ptr(LightUtil::GetPointLigthsColors()[0])); //point light color
	glUniform3fv(_uPointLightPos, pointLightCount, glm::value_ptr(LightUtil::GetPointLigthsPositions()[0])); //point light positiom
	glUniform3fv(_uPointAttenuation, pointLightCount, glm::value_ptr(LightUtil::GetPointLigthsAttenuations()[0])); //point light attenuation
	
	//send directional lights data
	int directionalLightCount = LightUtil::GetDirectionalLigthsCount();
	glUniform1f(_uDirectionalLightCount, directionalLightCount); //directional light count
	glUniform3fv(_uDirectionalLightColor, directionalLightCount, glm::value_ptr(LightUtil::GetDirectionalLigthsColors()[0])); //directional light color
    glUniform3fv(_uDirectionalLightDir, directionalLightCount, glm::value_ptr(LightUtil::GetDirectionalLigthsDirections()[0])); //directional light direction
	
	//send spot lights data
	int spotLightCount = LightUtil::GetSpotLigthsCount();
	glUniform1f(_uSpotLightCount, spotLightCount); //spot light count
	glUniform3fv(_uSpotLightColor, spotLightCount, glm::value_ptr(LightUtil::GetSpotLigthsColors()[0])); //spot light color
	glUniform3fv(_uSpotLightPos, spotLightCount, glm::value_ptr(LightUtil::GetSpotLigthsPositions()[0])); //spot light position
	glUniform3fv(_uSpotLightDir, spotLightCount, glm::value_ptr(LightUtil::GetSpotLigthsDirections()[0])); //spot light direction
	glUniform3fv(_uSpotLightAttenuation, spotLightCount, glm::value_ptr(LightUtil::GetSpotLigthsAttenuations()[0])); //spot light attenuation
	glUniform1fv(_uSpotLightAngle, spotLightCount, &LightUtil::GetSpotLigthsAngles()[0]); //spot light angle
	glUniform1fv(_uFallOffRate, spotLightCount, &LightUtil::GetSpotLigthsFallOffRates()[0]); //spot lights fall off rate

	//send camera position
	glUniform4fv(_uCameraPosition, 1, glm::value_ptr(_camera->getWorldPosition()));
}

void LitMaterial::setDiffuseColor(glm::vec3 pDiffuseColor) //set diffuse color
{
	_diffuseColor = pDiffuseColor;
}
void LitMaterial::setSpecularColor(glm::vec3 pSpecularColor) //set specular color
{
	_specularColor = pSpecularColor;
}