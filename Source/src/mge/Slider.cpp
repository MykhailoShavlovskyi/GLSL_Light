#include "mge/Slider.hpp"
#include "mge/config.hpp"


Slider::Slider(glm::vec2 pos, std::string name, std::string description, sf::Color color, sf::RenderWindow * aWindow)  : GameObject("slider", glm::vec3(0, 0, 0))
{
	_window = aWindow;
	
	//create slider sprite
	_sliderTexture.loadFromFile(config::MGE_TEXTURE_PATH + "slider.jpg");
	_sliderSprite.setTexture(_sliderTexture);
	_sliderSprite.setPosition(pos.x, pos.y);
	_sliderSprite.setColor(color);

	//create slider background sprite
	_backgroundTexture.loadFromFile(config::MGE_TEXTURE_PATH + "slider_background.jpg");
	_backgroundSprite.setTexture(_backgroundTexture);
	_backgroundSprite.setPosition(pos.x, pos.y);
	
	//create slider text
	_font.loadFromFile(config::MGE_FONT_PATH + "arial.ttf");
	_text.setString(name);
	_text.setFont(_font);
	_text.setCharacterSize(16);
	_text.setFillColor(sf::Color::White);
	_text.setPosition(pos.x, pos.y);

	//create slider description
	_description.setString(" -" + description);
	_description.setFont(_font);
	_description.setCharacterSize(16);
	_description.setFillColor(sf::Color::White);
	_description.setPosition(pos.x + _backgroundSprite.getGlobalBounds().width, pos.y);

	//define sliding length
	sliderLength = _backgroundSprite.getGlobalBounds().width - _sliderSprite.getGlobalBounds().width;

	startX = pos.x;
}


void Slider::update(float pStep)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!mouseButtonPressed)
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(*_window);
			sf::Vector2f spritePos = _sliderSprite.getPosition();
			glm::vec2 spriteSize = glm::vec2(_sliderSprite.getGlobalBounds().width, _sliderSprite.getGlobalBounds().height);

			//if mouse is on slider
			if (mousePos.x >= spritePos.x && mousePos.x <= spritePos.x + spriteSize.x
				&&mousePos.y >= spritePos.y && mousePos.y <= spritePos.y + spriteSize.y)
			{
				oldMousePos = mousePos;
				mouseButtonPressed = true;
			}
			
		}
		else
		{
			float spriteOldX = _sliderSprite.getPosition().x;
			float offset = sf::Mouse::getPosition(*_window).x - oldMousePos.x;

			//check bounds
			float newX = spriteOldX + offset;
			if (newX < 0 + startX)
			{
				newX = 0 + startX;
			}
			else if (newX > sliderLength + startX)
			{
				newX = sliderLength + startX;
			}
			else
			{
				oldMousePos = sf::Mouse::getPosition(*_window);
			}

			//move
			_sliderSprite.setPosition(newX, _sliderSprite.getPosition().y);
			_text.setPosition(newX, _sliderSprite.getPosition().y);
		}
	}
	else
	{
		mouseButtonPressed = false;
	}

	//draw
	_window->pushGLStates();
	_window->draw(_backgroundSprite);
	_window->draw(_sliderSprite);
	_window->draw(_text);
	_window->draw(_description);
	_window->popGLStates();
}

float Slider::getValue()
{
	return (_sliderSprite.getPosition().x-startX) / sliderLength;
}

void Slider::setValue(float value)
{
	if (value >= 0 && value <= 1)
	{
		float newX = startX + (_backgroundSprite.getGlobalBounds().width - _sliderSprite.getGlobalBounds().width)*value;
		float newY = _sliderSprite.getPosition().y;
		_sliderSprite.setPosition(sf::Vector2f(newX, newY));
		_text.setPosition(sf::Vector2f(newX, newY));
	}
}