#pragma once
#include <iostream>
#include <cmath>
#include "Header.hpp"
#include <SFML/Graphics.hpp>
#include "CommonComponent.hpp"
#include "Player.hpp"

class Enemy
{
private:
	sf::Vector2f pos;
	float velocity = ENEMY_SPEED;
	Player *playerPtr = nullptr;   // player의 위치를 얻어오기.
	EnemyApperance enemyApperance; // 기본정보.
	int health = 3;				   // 기본체력.

	// sf::Texture textureEnemy;
	sf::Sprite spriteEnemy;

public:
	Enemy();
	Enemy(EnemyApperance &eApp, Player *player, sf::Sprite sprite);
	~Enemy();
	void draw(sf::RenderWindow &window);
	void update(float dt);
	void setSpritePosition(sf::Vector2f pos);
	sf::Vector2f getSpritePosition();
	const sf::Sprite &getSprite() const;
	float getVelocity();
};