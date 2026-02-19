#include "Enemy.hpp"

Enemy::Enemy() {}

Enemy::Enemy(EnemyApperance &eApp, Player *player, sf::Sprite _spriteEnemy)
{
	enemyApperance = eApp;
	spriteEnemy = _spriteEnemy;
	velocity = eApp.eVelocity;

	playerPtr = player;

	spriteEnemy.setPosition(eApp.ePosition.x, eApp.ePosition.y);
	spriteEnemy.setScale(0.9f, 0.9f); // 스프라인트의 비율 원본 이 1.0, 절반이 0.5
}

Enemy::~Enemy()
{
}

void Enemy::draw(sf::RenderWindow &window)
{
	// window.draw(shape);
	window.draw(spriteEnemy);
}

void Enemy::update(float dt)
{
	sf::Vector2f playerPos = playerPtr->getSpritePosition();
	sf::Vector2f enemyPos = spriteEnemy.getPosition();

	float playerToEnemyX = playerPos.x - enemyPos.x;
	float playerToEnemyY = playerPos.y - enemyPos.y;

	float length = std::sqrtf(playerToEnemyX * playerToEnemyX + playerToEnemyY * playerToEnemyY);

	if (length > 0.1f)
	{
		playerToEnemyX /= length;
		playerToEnemyY /= length;

		sf::Vector2f movement;
		movement.x = playerToEnemyX * getVelocity() * dt;
		movement.y = playerToEnemyY * getVelocity() * dt;

		// sf::Vector2f nextPos;
		// nextPos += movement;
		// shape.setPosition(nextPos);
		spriteEnemy.move(movement);
	}
}

void Enemy::setSpritePosition(sf::Vector2f pos)
{
	spriteEnemy.setPosition(pos);
}

sf::Vector2f Enemy::getSpritePosition()
{
	return spriteEnemy.getPosition();
}

const sf::Sprite &Enemy::getSprite() const
{
	return spriteEnemy;
}

float Enemy::getVelocity()
{
	return velocity;
}
