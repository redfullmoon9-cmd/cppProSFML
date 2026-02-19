#pragma once
#include "Game2D.hpp"
#include "Header.hpp"
#include <cmath>

/*
 * [C++ 프로그래밍] 게임 만들기 실습 - 5. Pointer & Reference (2)예제 클래스화.
 */
class DrawTest3 : public Game2D
{
private:
	// player
	sf::Vector2f playerPosition;
	const float playerSize = 20.0f;
	sf::Color playerColor;
	sf::RectangleShape player;
	float playerSpeed = 2.0f;

	// Enemies
	float enemySpeed = 1.0f;
	sf::Vector2f *enemyPositions = nullptr;
	const float enemySize = 10.0f;
	sf::Color enemyColor;
	sf::CircleShape enemies[ENEMYCNT];

public:
	DrawTest3();
	~DrawTest3();
	void update(float dt) override;
	void render(sf::RenderWindow &r_window) override;

	void UpdatePlayerPosition(sf::Vector2f &playerPosition);
	void UpdateEnemiesPosition(float enemySpeed, sf::Vector2f *enemyPositions,
							   int enemyCount, sf::Vector2f playerPosition);
};