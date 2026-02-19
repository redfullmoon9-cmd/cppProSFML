#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Header.hpp"
#include "CommonComponent.hpp"
#include "Bullet.hpp"
#include <vector>
#include <cmath>
#include "InputManager.hpp"

class Player
{
private:
	PlayerApperance pApp;
	std::vector<Bullet *> bullets; // 포인터 할당 연습.
	sf::Clock bulletClock;		   // ge
	float fireInterval = 0.5f;	   // ge
	float bulletTimer = 0.f;

	BulletApperance bApp;
	sf::Sprite spritePlayer;
	InputManager *inputManager;

	float currentRotation = 0.0f;
	sf::Vector2f currentVelocity{0.f, 0.f};
	float rotationSpeed = 12.0f;

	// 조작감 조절 상수.
	const float acceleration = 2500.f; // 가속도.
	const float friction = 8.0f;	   // 마찰력
public:
	Player();
	~Player();
	void update(float dt);
	void draw(sf::RenderWindow &window);
	void setPlayer(PlayerApperance &PlayerApp, sf::Sprite sprite);
	sf::Vector2f getSpritePosition();
	void setSpritePosition(sf::Vector2f pos);
	void inputProcessTemp(float dt, int temp); // 코드 보관.
	void inputProcess(float dt);			   // 26. 01.08 new
	void fireBullet(float dt);
	BulletApperance &getBulletApp();

	void setInputManager(InputManager *manager);
};