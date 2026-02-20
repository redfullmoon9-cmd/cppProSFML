#pragma once
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "InputManager.hpp" //imputManager

class Game2D//test 
{
private:
	int width = 0;
	int height = 0;
	std::string title = "";

	std::unique_ptr<sf::RenderWindow> r_window;
	InputManager inputManager; // 26.01.08

protected:
public:
	Game2D();
	Game2D(const std::string &title, const int &width, const int &height);
	~Game2D() {};
	Game2D &init();
	void run();
	virtual void render(sf::RenderWindow &r_window) {}
	virtual void update(float dt)
	{
		// draw;
	}
	bool isKeyPressed();
	InputManager &getInputManager();
};
