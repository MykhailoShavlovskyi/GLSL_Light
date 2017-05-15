#include <glm.hpp>
#include <iostream>
#include <string>
using namespace std;

#include "mge/core/Renderer.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"

#include "mge/core/Camera.hpp"

#include "mge/core/GameObject.hpp"
#include "mge/materials/AbstractMaterial.hpp"

#include "mge/materials/LitMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/behaviours/OrbitBehaviour.hpp"
#include "mge/behaviours/LookAt.hpp"

#include "mge/util/DebugHud.hpp"

#include "mge/config.hpp"
#include "mge/MGEDemo.hpp"
#include "mge/core/Light.hpp"
#include "mge/util/LightUtil.hpp"

#include "mge/Slider.hpp"

//construct the game class into _window, _renderer and hud (other parts are initialized by build)

Slider * diffuseColorSliderR;
Slider * diffuseColorSliderG;
Slider * diffuseColorSliderB;
Slider * specularColorSliderR;
Slider * specularColorSliderG;
Slider * specularColorSliderB;
Slider * snininessSlider;

Slider * lightColorSliderR;
Slider * lightColorSliderG;
Slider * lightColorSliderB;
Slider * attenuationSliderC1;
Slider * attenuationSliderC2;
Slider * attenuationSliderC3;
Slider * angleSlider;
Slider * fallOffRateSlider;
Slider * typeSlider;

Slider * lightColorSliderR2;
Slider * lightColorSliderG2;
Slider * lightColorSliderB2;
Slider * attenuationSliderC12;
Slider * attenuationSliderC22;
Slider * attenuationSliderC32;
Slider * angleSlider2;
Slider * fallOffRateSlider2;
Slider * typeSlider2;

Light * light;
Light * light2;
Light * light3;

LitMaterial* litMaterial;

MGEDemo::MGEDemo():AbstractGame (),_hud(0)
{
}

void MGEDemo::initialize() {
    //setup the core part
    AbstractGame::initialize();

    //setup the custom part
	cout << "Initializing HUD" << endl;
	_hud = new DebugHud(_window);
	cout << "HUD initialized." << endl << endl;
}

//build the game _world
void MGEDemo::_initializeScene()
{
    _renderer->setClearColor(0,0,0);

    //add camera first (it will be updated last)
    Camera* camera = new Camera ("camera", glm::vec3(0,5,9));
    camera->rotate(glm::radians(-40.0f), glm::vec3(1,0,0));
    _world->add(camera);
    _world->setMainCamera(camera);

    //MESHES
    Mesh* planeMeshDefault = Mesh::load (config::MGE_MODEL_PATH+"plane.obj");
    Mesh* suzannaMeshF = Mesh::load (config::MGE_MODEL_PATH+"suzanna_smooth.obj");
    Mesh* teapotMeshS = Mesh::load (config::MGE_MODEL_PATH+"teapot_smooth.obj");
    Mesh* cubeMeshF = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");

	//MATERIALS
	litMaterial = new LitMaterial (glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), 4, _world->getMainCamera());

    //SCENE SETUP
    GameObject* monkey = new GameObject ("monkey", glm::vec3(0,1,0));
    monkey->setMesh (suzannaMeshF);
    monkey->setMaterial(litMaterial);
    monkey->setBehaviour (new RotatingBehaviour());
    _world->add(monkey);

	GameObject* cube = new GameObject("cube", glm::vec3(4, 1, 0));
	cube->setMesh(cubeMeshF);
	cube->setMaterial(litMaterial);
	_world->add(cube);
	cube->scale(glm::vec3(2,2,1));

	GameObject* teapot = new GameObject("teapot", glm::vec3(-4, 1, 0));
	teapot->setMesh(teapotMeshS);
	teapot->setMaterial(litMaterial);
	_world->add(teapot);

	GameObject* wall = new GameObject("wall", glm::vec3(0, 1, -20));
	wall->setMesh(cubeMeshF);
	wall->setMaterial(litMaterial);
	_world->add(wall);
	wall->scale(glm::vec3(10, 10, 1));

	camera->setBehaviour(new OrbitBehaviour(15, 45, 0.5, monkey, _window));

	//LIGHTS
	light = new Light("light", glm::vec3(0, 1, 2), glm::vec3(1, 1, 1), Light::Type::POINT, glm::vec3(1, 0, 0));
	light2 = new Light("light2", glm::vec3(4, 1, 2), glm::vec3(1, 1, 1), Light::Type::POINT, glm::vec3(1, 0, 0));
	light3 = new Light("light3", glm::vec3(4, 1, 4), glm::vec3(0, 1, 0), Light::Type::POINT, glm::vec3(1, 0, 0));
	_world->add(light);
	_world->add(light2);
	//_world->add(light3);
	LightUtil::AddLight(light);
	LightUtil::AddLight(light2);
	//LightUtil::AddLight(light3);

	//SLIDERS
	diffuseColorSliderR = new Slider(glm::vec2(0, 70), "", "diffuse", sf::Color::Red, _window);
	diffuseColorSliderR->setValue(1);
	_world->add(diffuseColorSliderR);
	diffuseColorSliderG = new Slider(glm::vec2(0, 100), "", "diffuse", sf::Color::Green, _window);
	diffuseColorSliderG->setValue(1);
	_world->add(diffuseColorSliderG);
	diffuseColorSliderB = new Slider(glm::vec2(0, 130), "", "diffuse", sf::Color::Blue, _window);
	diffuseColorSliderB->setValue(1);
	_world->add(diffuseColorSliderB);
	specularColorSliderR = new Slider(glm::vec2(0, 190), "", "specular", sf::Color::Red, _window);
	specularColorSliderR->setValue(1);
	_world->add(specularColorSliderR);
	specularColorSliderG = new Slider(glm::vec2(0, 220), "", "specular", sf::Color::Green, _window);
	specularColorSliderG->setValue(1);
	_world->add(specularColorSliderG);
	specularColorSliderB = new Slider(glm::vec2(0, 250), "", "specular", sf::Color::Blue, _window);
	specularColorSliderB->setValue(1);
	_world->add(specularColorSliderB);
	snininessSlider = new Slider(glm::vec2(0, 310), "", "shininess", sf::Color::White, _window);
	_world->add(snininessSlider);

	lightColorSliderR = new Slider(glm::vec2(800, 20), "", "light1", sf::Color::Red, _window);
	_world->add(lightColorSliderR);
	lightColorSliderG = new Slider(glm::vec2(800, 50), "", "light1", sf::Color::Green, _window);
	_world->add(lightColorSliderG);
	lightColorSliderB = new Slider(glm::vec2(800, 80), "", "light1", sf::Color::Blue, _window);
	lightColorSliderB->setValue(1);
	_world->add(lightColorSliderB);
	attenuationSliderC1 = new Slider(glm::vec2(800, 140), "", "light1 intensity", sf::Color::White, _window);
	_world->add(attenuationSliderC1);
	attenuationSliderC2 = new Slider(glm::vec2(800, 170), "", "light1 linear attenuation", sf::Color::White, _window);
	_world->add(attenuationSliderC2);
	attenuationSliderC3 = new Slider(glm::vec2(800, 200), "", "light1 quad attenuation", sf::Color::White, _window);
	_world->add(attenuationSliderC3);
	typeSlider = new Slider(glm::vec2(800, 260), "", "light1 type(point, dir, spot)", sf::Color::White, _window);
	_world->add(typeSlider);
	angleSlider = new Slider(glm::vec2(800, 320), "", "light1 angle(spot light)", sf::Color::White, _window);
	angleSlider->setValue(1./ 180 *30);
	_world->add(angleSlider);
	fallOffRateSlider = new Slider(glm::vec2(800, 350), "", "light1 fall of rate(spot light)", sf::Color::White, _window);
	fallOffRateSlider->setValue(1. / 180 * 5);
	_world->add(fallOffRateSlider);

	lightColorSliderR2 = new Slider(glm::vec2(800, 540), "", "light2", sf::Color::Red, _window);
	_world->add(lightColorSliderR2);
	lightColorSliderG2 = new Slider(glm::vec2(800, 570), "", "light2", sf::Color::Green, _window);
	_world->add(lightColorSliderG2);
	lightColorSliderB2 = new Slider(glm::vec2(800, 600), "", "light2", sf::Color::Blue, _window);
	_world->add(lightColorSliderB2);
	attenuationSliderC12 = new Slider(glm::vec2(800, 660), "", "light2 intensity", sf::Color::White, _window);
	_world->add(attenuationSliderC12);
	attenuationSliderC22 = new Slider(glm::vec2(800, 690), "", "light2 linear attenuation", sf::Color::White, _window);
	_world->add(attenuationSliderC22);
	attenuationSliderC32 = new Slider(glm::vec2(800, 720), "", "light2 quad attenuation", sf::Color::White, _window);
	_world->add(attenuationSliderC32);
	typeSlider2 = new Slider(glm::vec2(800, 780), "", "light2 type(point, dir, spot)", sf::Color::White, _window);
	_world->add(typeSlider2);
	angleSlider2 = new Slider(glm::vec2(800, 840), "", "light2 angle(spot light)", sf::Color::White, _window);
	angleSlider2->setValue(1. / 180 * 30);
	_world->add(angleSlider2);
	fallOffRateSlider2 = new Slider(glm::vec2(800, 870), "", "light2 fall of rate(spot light)", sf::Color::White, _window);
	fallOffRateSlider2->setValue(1. / 180 * 5);
	_world->add(fallOffRateSlider2);  
}

void MGEDemo::_render() 
{
    AbstractGame::_render();
    _updateHud();
}

void MGEDemo::_updateHud() 
{
	//get values from sliders
	glm::vec3 diffuseColor = glm::vec3(diffuseColorSliderR->getValue(), diffuseColorSliderG->getValue(), diffuseColorSliderB->getValue());
	glm::vec3 specularColor = glm::vec3(specularColorSliderR->getValue(), specularColorSliderG->getValue(), specularColorSliderB->getValue());
	int shininess = snininessSlider->getValue() * 16 * snininessSlider->getValue() * 16 + 1; //value from 1 to 257;

	glm::vec3 lightColor = glm::vec3(lightColorSliderR->getValue(), lightColorSliderG->getValue(), lightColorSliderB->getValue());
	glm::vec3 attenuation = glm::vec3(attenuationSliderC1->getValue()*10+1, attenuationSliderC2->getValue(), attenuationSliderC3->getValue());//c1 is from 1 to 10, c2 is  from 0 to 1, c3 is  from 0 to 1, 
	Light::Type type;
	if (typeSlider->getValue() < 0.33) { type = Light::Type::POINT; }
	else if (typeSlider->getValue() < 0.66) { type = Light::Type::DIRRECTIONAL; }
	else { type = Light::Type::SPOT; }
	float angle = angleSlider->getValue() * 180 + 0.001;
	float fallOffRate = fallOffRateSlider->getValue() * 180 + 0.001;

	glm::vec3 lightColor2 = glm::vec3(lightColorSliderR2->getValue(), lightColorSliderG2->getValue(), lightColorSliderB2->getValue());
	glm::vec3 attenuation2 = glm::vec3(attenuationSliderC12->getValue() * 10 + 1, attenuationSliderC22->getValue(), attenuationSliderC32->getValue());//c1 is from 1 to 10, c2 is  from 0 to 1, c3 is  from 0 to 1, 
	Light::Type type2;
	if (typeSlider2->getValue() < 0.33) { type2 = Light::Type::POINT; }
	else if (typeSlider2->getValue() < 0.66) { type2 = Light::Type::DIRRECTIONAL; }
	else { type2 = Light::Type::SPOT; }
	float angle2 = angleSlider2->getValue() * 180 + 0.001;
	float fallOffRate2 = fallOffRateSlider2->getValue() * 180 + 0.001;

	//update material and light properties
	litMaterial->_diffuseColor = diffuseColor;
	litMaterial->_specularColor = specularColor;
	litMaterial->_shininess= shininess;

	light->_lightColor = lightColor;
	light->model->setMaterial(new ColorMaterial(lightColor));
	light->_attenuation = attenuation;
	light->changeType(type);
	light->setAngle(angle);
	light->setFallOffRate(fallOffRate);

	light2->_lightColor = lightColor2;
	light2->model->setMaterial(new ColorMaterial(lightColor2));
	light2->_attenuation = attenuation2;
	light2->changeType(type2);
	light2->setAngle(angle2);
	light2->setFallOffRate(fallOffRate2);

	//update hud
    string debugInfo = "";
    debugInfo += string ("FPS:") + std::to_string((int)_fps)+"\n";

    _hud->setDebugInfo(debugInfo);
    _hud->draw();
}

MGEDemo::~MGEDemo()
{
	//dtor
}
