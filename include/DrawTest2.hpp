#pragma once

#include "Game2D.hpp"
#include "Header.hpp"
#include "CommonComponent.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include <random>


class DrawTest2: public Game2D {
private: 
	PlayerApperance playerApperance;
	Player player; 
	EnemyApperance enemyApperance; 
	Enemy* enemies; 

	sf::Texture textureEnemy; 
	sf::Sprite spriteEnemy; 
	sf::Texture texturePlayer; 
	sf::Sprite spritePlayer; 

	// 에너미들의 위치와 색갈을 랜덤하게 처리.  
	std::random_device rd;
	std::mt19937 gen{ rd() }; 
	std::uniform_int_distribution<int> randIntX{ 1, 1024 }; 
	std::uniform_int_distribution<int> randIntY{ 1, 768 }; 
	//std::uniform_int_distribution<int> randColor{ 1, 255 }; 
	std::uniform_real_distribution<float> randSpeed{ 10.f, 80.f }; 
public: 
	DrawTest2(); 
	~DrawTest2(); 
	void update(float dt) override; 
	void render(sf::RenderWindow& r_window) override; 

};
