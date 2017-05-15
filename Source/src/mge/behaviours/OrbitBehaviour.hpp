#ifndef ORBITBEHAVIOUR_H
#define ORBITBEHAVIOUR_H

#include <glm.hpp>
#include "mge/behaviours/AbstractBehaviour.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

class OrbitBehaviour : public AbstractBehaviour
{
    public:
        OrbitBehaviour(float distance, float maxTiltAngle, float speed, GameObject * pTarget, sf::RenderWindow * window);
        virtual ~OrbitBehaviour();

        virtual void update(float pStep);

    private:
		OrbitBehaviour(const OrbitBehaviour&);
		OrbitBehaviour& operator=(const OrbitBehaviour&);
		void setIntitialPosition();
		void lookAtTarget();
		void getInput();

        sf::RenderWindow * _window;
        GameObject * _target;
		float _distance;
        float _maxTiltAngle;
        float _speed;

		bool _start = true;

		float currentYrotation = 0;
		float currentXrotation = 0;
		
		glm::vec3 _targetToCameraDistance;

		bool _spaceDown = false;
		bool _blockMovement = false;
		
};

#endif // ORBITBEHAVIOUR_H
