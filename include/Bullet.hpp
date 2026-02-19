#pragma once 
#include <iostream>
#include <SFML/Graphics.hpp>
#include "CommonComponent.hpp"

//26. 01.05
class Bullet {
private: 
	sf::CircleShape shape; 
	float bulletSpeed=0.f; 
	float bulletDirection = 1.0f; 
	//sf::Vector2f bulletPosition;
	int damage= 0; // 충돌 데미지  

public: 
	Bullet(); 
	Bullet(BulletApperance bApp);
	~Bullet();
	void draw(sf::RenderWindow& window); 
	void update(float dt); 
	bool isCollide(); 
	sf::Vector2f getPosition(); 
};