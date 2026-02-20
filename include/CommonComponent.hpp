#pragma once 
#include <SFML/Graphics.hpp>

//3로 나누어진것 하나로 합쳐야. 
struct PlayerApperance {
	sf::Vector2f pSize{ 0.0f, 0.0f };
	sf::Vector2f pPosition{ 0.f, 0.f }; 
	float pVelocity = 0.0f;
	sf::Color color = { 255, 173, 10 };
};

struct EnemyApperance {
	sf::Vector2f eSize{ 0.0f, 0.0f }; 
	sf::Vector2f ePosition{ 0.0f, 0.0f }; 
	float eVelocity = 0.0f; 
	sf::Color color = sf::Color::Cyan; 
};

struct BulletApperance {
	float bRadius = 0.f; 
	sf::Vector2f bPosition; 
	float bVelocity = 0.0f; 
	sf::Color color{ 255, 0, 0 };
};
