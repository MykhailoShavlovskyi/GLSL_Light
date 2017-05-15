#ifndef LITMATERIAL_H
#define LITMATERIAL_H

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/core/Light.hpp"

class LitMaterial : public AbstractMaterial
{
    public:
        LitMaterial(glm::vec3 pDiffuseColor, glm::vec3 pSpecularColor, int pShininess, Camera * pCamera);
        virtual ~LitMaterial();
        virtual void render(Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

        void setDiffuseColor (glm::vec3 pDiffuseColor);
		void setSpecularColor(glm::vec3 pSpecularColor);

		glm::vec3 _diffuseColor;
		glm::vec3 _specularColor;
		int _shininess;

    private:
		static void _lazyInitializeShader();
        static ShaderProgram* _shader;

		//vertex shader parameters
		static GLint _aVertex;
		static GLint _aNormal;
		static GLint _aUV;
        static GLint _uMVPMatrix;
		static GLint _uModelMatrix;

		//fragment shader parameters
        static GLint _uDiffuseColor;
		static GLint _uSpecularColor;
		static GLint _uShininess;

		static GLint _uPointLightCount;
        static GLint _uPointLightColor;
		static GLint _uPointLightPos;
		static GLint _uPointAttenuation;

		static GLint _uDirectionalLightCount;
		static GLint _uDirectionalLightColor;
		static GLint _uDirectionalLightDir;

		static GLint _uSpotLightCount;
		static GLint _uSpotLightColor;
		static GLint _uSpotLightPos;
		static GLint _uSpotLightDir;
		static GLint _uSpotLightAttenuation;
		static GLint _uSpotLightAngle;
		static GLint _uFallOffRate;

		static GLint _uCameraPosition;

		Camera * _camera;

		bool pressed = false;
};

#endif // COLORMATERIAL_H

