#include "Bullet.hpp"

Bullet::Bullet(BulletApperance bApp)
{
	bulletSpeed = bApp.bVelocity; 
	shape.setFillColor(bApp.color); 
	shape.setPosition(bApp.bPosition); 
	shape.setRadius(bApp.bRadius); 
}

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::draw(sf::RenderWindow& window)
{
	//std::cout << "in bullet draw " << std::endl;
	window.draw(shape); 
}

void Bullet::update(float dt)
{
	sf::Vector2f movement;
	movement.x = bulletSpeed * dt;
	movement.y = 0.0f;

	shape.move(movement); 
}

bool Bullet::isCollide()
{
	return false;
}

sf::Vector2f Bullet::getPosition() {
	return shape.getPosition(); 
}
