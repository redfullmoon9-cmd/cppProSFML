#include "Player.hpp"

Player::Player():inputManager(nullptr) { }

//26.01.06 rect에서 스프라이트로 변경. 
void Player::setPlayer(PlayerApperance& playerApp, sf::Sprite _spritePlayer)
{
	pApp = playerApp; 
	spritePlayer = _spritePlayer; 
	spritePlayer.setPosition(100.f, 100.f); 
	spritePlayer.setScale(1.f, 1.f); 
}


Player::~Player()
{	//벡터내의 개별 요쇼를 지우고 
	for (Bullet* bullet : bullets) {
		delete bullet; 
	}
	bullets.clear(); //벡터를 비워 준다. 
}

/* 26. 01. 05 bullet update  
* 코드 구성 주의 깊에 보아야--> 메모리 해제 부분. 
*/
void Player::update(float dt) {
	inputProcess(dt); //키보드 입력 
	fireBullet(dt); //자동으로 총알 발사 하는 로직... 
	for (auto it = bullets.begin(); it != bullets.end(); ) {
		(*it)->update(dt); //vector<Bullet* > 
		
		if ((*it)->getPosition().x > SCREEN_WIDTH) { //화면을 넘어선 총알들 검사. 
			delete* it;  //메모리 해제 
			it = bullets.erase(it); //벡터에서 포인터 제거 후 다음 요소를 가르킴. 
		}
		else {
			++it; 
		}
	}
}

void Player::draw(sf::RenderWindow& window)
{
	//window.draw(rect); 
	window.draw(spritePlayer); 
	for(auto& bullet:bullets) {
		bullet->draw(window); 
		
	}
}

//26.02.03 일단 동작구조로 만들고 향후 Map 구조로 작성. 
// 변경 액션바이딩 방식으로 ...현재의 코드와 아래 action mapping 코드와 비교 검토용.  
void Player::inputProcessTemp(float dt, int temp)
{
	//sf::Vector2f pos = rect.getPosition(); 
	sf::Vector2f pos = spritePlayer.getPosition(); 
	
	sf::Vector2f direction{ 0.0f, 0.0f }; 

	//SFML의 키를 그대로 사용 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		direction.y -= 1.0f; 
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		direction.y += 1.0f; 
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		direction.x -= 1.0f; 
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
 		direction.x += 1.0f; 
	}
	
	sf::Vector2f movement= direction * pApp.pVelocity * dt; 
	sf::Vector2f nextPos = pos + movement; 

	//경계 제한. 
	if (nextPos.x < 0) { nextPos.x = 0;  }
	if (nextPos.x > SCREEN_WIDTH_M - pApp.pSize.x) { nextPos.x = SCREEN_WIDTH_M - pApp.pSize.x;  }
	if (nextPos.y < 0) { nextPos.y = 0;  }
	if (nextPos.y > SCREEN_HEIGHT_M - pApp.pSize.y) { nextPos.y = SCREEN_HEIGHT_M - pApp.pSize.y; }

	spritePlayer.setPosition(nextPos); 

}

//26 01.08 action mapping 방식으로 전환. 
void Player::inputProcess(float dt) {
	unsigned int mode = 1; // 0. 테스트 코드. 1. 방향 보간, 마찰력, 가속도등 적용. 
	sf::Vector2f pos = spritePlayer.getPosition(); 
	sf::Vector2f direction{ 0.f, 0.f }; 
	sf::Vector2f nextPos{ 0.f, 0.f };

	//액션 매핑한 이후 axis를 이용한 키맵 방식. 
	direction.x = inputManager->GetAxisValue("MoveHorizontal"); 
	direction.y = inputManager->GetAxisValue("MoveVertical"); 
	
	//26. 01. 12. 스프라이트 움직임을 각도로 제어 --너무 딱딱함 atan2()함수 사용으로 변경. 
	// 코드 더 검토해서 익숙해 지도록 
	if (mode == 0) {
		if (direction.x == 1) {
			spritePlayer.setRotation(90); 
			std::cout << " direction : " << direction.x << std::endl; 

		}
		else if (direction.x == -1) {
			spritePlayer.setRotation(-90); 
			std::cout << " direction : " << direction.x << std::endl; 

		}
		else if (direction.y == 1) {
			spritePlayer.setRotation(-180); 
			std::cout << " direction y: " << direction.y << std::endl; 
		}
		else if (direction.y == -1) {
			spritePlayer.setRotation(0); 
			std::cout << " direction y: " << direction.y << std::endl; 
		}

		sf::Vector2f movement = direction * pApp.pVelocity * dt;
		nextPos = pos + movement;
	}
	else if (mode == 1) {
		//부드러운 이동 : 마찰력 friction 과 가속도 acceleration을 이용한 이동. 
		if (direction.x != 0 || direction.y != 0) {
			//벡터의 정규화, 대각선 이동 속도를 일정하게 유지 하게 함. 
			float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
			direction /= length;
			//가속도 적용. 
			currentVelocity += direction * acceleration * dt;
		}
		//입력이 없을때 마찰력을 적용해서 서서히 멈춤. 
		else {
			currentVelocity -= currentVelocity * friction * dt;
		}

		//최대 속도 제한 -- 정규화 하겠다는 것 까지 이해 . 코드가 이해가 잘 안감. 
		float speed = std::sqrt(currentVelocity.x * currentVelocity.x + currentVelocity.y * currentVelocity.y);
		if (speed > pApp.pVelocity) {
			currentVelocity = (currentVelocity / speed) * pApp.pVelocity;
		}

		// atan2()함수를 이용해서 4방향이 아니 모든 방향에 대한 각도 계산. 
		// 현재 각도와 움직일 각도사이를 보간
		if (direction.x != 0 || direction.y != 0) {
			//목표각도 계산 atan()은 radian을 반환하므로 π/2로 각도로 변환. 
			float targetAngle = std::atan2(direction.y, direction.x) * 180.f / 3.14159265f;

			float angleDiff = targetAngle - currentRotation;
			while (angleDiff > 180.0f) angleDiff -= 360.0f;
			while (angleDiff < -180.0f) angleDiff += 360.0f;

			//Lerp(보간) 방식을 사용한 부드러운 회전 - 현재각도를 목표각도 방향으로 보간
			currentRotation += angleDiff * rotationSpeed * dt;

			//SFML에서 오른쪽이 0도 이므로 오프셋을 더함. 90도 
			//spritePlayer.setRotation(targetAngle + 90.0f); 
			spritePlayer.setRotation(currentRotation + 90.0f); //90도의 offset을 적용하지 않을 경우 이상한 움직임. 
		}

		nextPos = spritePlayer.getPosition() + ( currentVelocity * dt); 
	}

	//향후 대시 처리. 
	float speedMultiplayer = inputManager->isActionActive("Dash") ? 2.0f : 1.0f; 
	//dash시가 옵션으로 있는 경우. 
	//sf::Vector2f movement = direction * pApp.pVelocity * speedMultiplayer * dt;

	//점프 처리. -- space key
	if (inputManager->isActionActive("Jump")) {
		std::cout << "jum .. p " << std::endl; 
	}

	// 공격처리. J key. 
	if (inputManager->isActionActive("Attack")) {
		std::cout << " attack " << std::endl; 
	}

	if (nextPos.x < 0) { nextPos.x = 0; }
	if (nextPos.x > SCREEN_WIDTH_M - pApp.pSize.x) { nextPos.x = SCREEN_WIDTH_M - pApp.pSize.x; }
	if (nextPos.y < 0) { nextPos.y = 0; }
	if (nextPos.y > SCREEN_HEIGHT_M - pApp.pSize.y) { nextPos.y = SCREEN_HEIGHT_M - pApp.pSize.y; }

	spritePlayer.setPosition(nextPos);
}

void Player::fireBullet(float dt)
{	
	//매 프레임 0.016 초를 더 함.  
	bulletTimer += dt; 
	if (bulletTimer >= fireInterval) {

		BulletApperance bulletAppr = getBulletApp(); 
		bulletAppr.bPosition = getSpritePosition(); 
		bulletAppr.bRadius = 6.0f; 
		bulletAppr.bVelocity = 150.0f; 
		bulletAppr.color = sf::Color::Red; 
		
		Bullet* bullet = new Bullet(bulletAppr); //동적할당 후 --> 메모리 해제 잊지 않기. 
		bullets.push_back(bullet); 

		bulletTimer = 0.0f; //타이머의 누적 시간이 인터벌 시간을 지나면 다시 초기화. 
	}
}

BulletApperance& Player::getBulletApp()
{
	return bApp; 
}


sf::Vector2f Player::getSpritePosition()
{
	return spritePlayer.getPosition(); 
}
void Player::setSpritePosition(sf::Vector2f pos)
{
	spritePlayer.setPosition(pos);
}

void Player::setInputManager(InputManager* manager)
{
	inputManager = manager; 
}
