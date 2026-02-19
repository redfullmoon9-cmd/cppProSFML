#pragma once
#include "Game2D.hpp"
#include <SFML/Graphics.hpp>
#include "InputManager.hpp"

class DrawTest4 : public Game2D
{
private:
public:
	DrawTest4();
	~DrawTest4();
	void update(float deltaTime) override;
	void render(sf::RenderWindow window);
};