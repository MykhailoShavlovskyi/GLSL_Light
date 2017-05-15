#ifndef SLIDER_H
#define SLIDER_H

#include <string>
#include "mge/core/GameObject.hpp"
#include <SFML/Graphics.hpp>


class Slider : public GameObject
{
public:
	Slider(glm::vec2 pos, std::string name, std::string description, sf::Color color, sf::RenderWindow * aWindow);
	void update(float pStep) override;
	float getValue();
	void setValue(float value);

private:
	sf::RenderWindow *_window;
	sf::Sprite _sliderSprite;
	sf::Texture _sliderTexture;
	sf::Sprite _backgroundSprite;
	sf::Texture _backgroundTexture;
	sf::Font _font;
	sf::Text _text;
	sf::Text _description;

	float sliderLength;
	float startX;

	bool mouseButtonPressed = false;
	sf::Vector2i oldMousePos;
};

#endif 