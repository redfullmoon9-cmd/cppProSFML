#include "DrawTest2.hpp"

DrawTest2::DrawTest2()
{
	texturePlayer.loadFromFile(FIGHT_IMG); 
	spritePlayer.setTexture(texturePlayer); 

	textureEnemy.loadFromFile(ALIEN1_IMG); 
	spriteEnemy.setTexture(textureEnemy); 

	playerApperance.pSize = { 30.f, 30.f };
	playerApperance.pVelocity = 200.0f;
	playerApperance.pPosition = { 100.0f, 100.0f };
	player.setPlayer(playerApperance, spritePlayer);
	player.setInputManager(&getInputManager()); //inputManager 연결. 

	enemies = new Enemy[ENEMYCNT];
	enemyApperance.eSize={ 20.f, 20.f};
	for (int i = 0; i < ENEMYCNT; i++) {
		enemyApperance.ePosition = { static_cast<float>(randIntX(gen)), static_cast<float>(randIntY(gen)) }; 
		enemyApperance.eVelocity = randSpeed(gen); 

		enemies[i] = Enemy(enemyApperance, &player, spriteEnemy);
	}
}

DrawTest2::~DrawTest2() { delete[] enemies;  }

void DrawTest2::update(float dt) {
	/*if (getInputManager().isActionActive("Pause")) {
		std::cout << "Game paused " << std::endl; 
	}*/

	player.update(dt); 

	for (int i = 0; i < ENEMYCNT; i++) {
		enemies[i].update(dt); 
	}
}

void DrawTest2::render(sf::RenderWindow& r_window)
{
	player.draw(r_window); 
	for (int i = 0; i < ENEMYCNT; i++) {
		enemies[i].draw(r_window); 
	}
}






