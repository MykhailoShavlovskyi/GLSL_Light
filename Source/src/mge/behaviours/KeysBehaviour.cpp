#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include <SFML/Window/Keyboard.hpp>

KeysBehaviour::KeysBehaviour(float pMoveSpeed, float pTurnSpeed): AbstractBehaviour(), _moveSpeed(pMoveSpeed), _turnSpeed(pTurnSpeed)
{
}

KeysBehaviour::~KeysBehaviour()
{
}

void KeysBehaviour::update( float pStep )
{
	float moveSpeedX = 0.0f; //default if no keys
	float moveSpeedZ = 0.0f;
	float moveSpeedY = 0.0f;

	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Down)) {
		moveSpeedZ = .1f;
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up )) {
		moveSpeedZ = -.1f;
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left)) {
		moveSpeedX = -.1f;
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right)) {
		moveSpeedX = .1f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		moveSpeedY = .1f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		moveSpeedY = -.1f;
	}
	//translate the object in its own local space
	_owner->translate( glm::vec3(moveSpeedX, moveSpeedY, moveSpeedZ) );


	//rotate the object in its own local space
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::R )) 
	{
		_owner->rotate( glm::radians(5.0f), glm::vec3(0.0f, 1.0f, 0.0f ) );
	}
}
