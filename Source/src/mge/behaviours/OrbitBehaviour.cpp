#include "mge/behaviours/OrbitBehaviour.hpp"
#include <glm.hpp>
#include "mge/core/GameObject.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#define M_PI 3.14
#include <math.h>

OrbitBehaviour::OrbitBehaviour(float distance, float maxTiltAngle, float speed, GameObject * pTarget, sf::RenderWindow * window): AbstractBehaviour(),
_target(pTarget), _distance(distance), _maxTiltAngle(maxTiltAngle), _speed(speed), _window(window)
{

}

OrbitBehaviour::~OrbitBehaviour()
{
    //dtor
}

void OrbitBehaviour::update(float pStep)
{
	if (_start)
	{
		setIntitialPosition();
		_start = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (!_spaceDown)
		{
			_spaceDown = true;
			_blockMovement = !_blockMovement;
		}
	}
	else
	{
		_spaceDown = false;
	}
	if (!_blockMovement)
	{
		getInput();
	}
}

void OrbitBehaviour::getInput()
{
	//get mouse and window parameters
	glm::vec2 mousePos = glm::vec2(sf::Mouse::getPosition(*_window).x, sf::Mouse::getPosition(*_window).y);
	glm::vec2 windowCenter = glm::vec2(_window->getSize().x / 2, _window->getSize().y / 2);
	
	//translate mouse position into rotation angles.
	float rotationX = _maxTiltAngle / (windowCenter.y / (mousePos.y - windowCenter.y));
	float rotationY = (180 / (windowCenter.x / (mousePos.x - windowCenter.x))) * _speed;
	if (rotationX > _maxTiltAngle)
	{
		rotationX = _maxTiltAngle;
	}
	else  if (rotationX < -_maxTiltAngle)
	{
		rotationX = -_maxTiltAngle;
	}

	//rotate around y axis
	glm::vec3 newDistance = glm::rotate(_targetToCameraDistance, glm::radians(rotationY), glm::vec3(0, 1, 0)); 
	//rotate around x axis		
	newDistance = glm::rotate(newDistance, glm::radians(rotationX), glm::normalize(glm::cross(glm::vec3(0, 1, 0), newDistance)));

	//set position
	_owner->setLocalPosition(_target->getWorldPosition() + newDistance);
	
	lookAtTarget();
}

void OrbitBehaviour::setIntitialPosition()
{
	glm::vec3 pos = _owner->getWorldPosition();
	_owner->setLocalPosition(glm::vec3(pos.x, _target->getWorldPosition().y, pos.z));

	_targetToCameraDistance = _owner->getWorldPosition() - _target->getWorldPosition();
	_targetToCameraDistance = glm::normalize(_targetToCameraDistance);
	_targetToCameraDistance = _targetToCameraDistance * _distance;

	_owner->setLocalPosition( _target->getWorldPosition() + _targetToCameraDistance);
}

void OrbitBehaviour::lookAtTarget()
{
	glm::vec3 forward = glm::normalize(_owner->getLocalPosition() - _target->getLocalPosition());
	glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), forward));
	glm::vec3 up = glm::cross(forward, right);

	_owner->setTransform(
		glm::mat4(glm::vec4(right, 0), glm::vec4(up, 0), glm::vec4(forward, 0), glm::vec4(_owner->getLocalPosition(), 1))
		);
}