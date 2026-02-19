#include "Game2D.hpp"
#include "Header.hpp"
#include "DrawTest4.hpp"
/* 1.08 키보드 이벤트 변경 추가. */


Game2D::Game2D() : title(TITLE), width(SCREEN_WIDTH_M), height(SCREEN_HEIGHT_M) {
	init(); 
}
//생성자 위임이 문제??? -- 
Game2D::Game2D(const std::string& title, const int& width, const int& height) :Game2D(){
	this->title = title; 
	this->width = width; 
	this->height = height; 
}

// 26. 2.1 키 이벤트를 상속받는 클래스의 update에서 처리 
Game2D& Game2D::init() {
	r_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title);

	//초당 프레임을 60초로 체한
	r_window->setFramerateLimit(60); 
	//키 바인딩. ==> 키 바인딩은 하위 클래스 에서 --> event를 검사하게 될경우 여기가 적합. 
	inputManager.setupInputBindings(); //inputManager애서 하는 것으로 로직상.. 어쩔 수 없음.  
	return *this; 
}

//1.29 시간을 정확히 측정하기 위해서 시계 추가 
void Game2D::run() {
	sf::Clock  clock; 
	
	while (r_window->isOpen()) {
		sf::Time elapsed = clock.restart();
		float dt = elapsed.asSeconds(); 

		//매프레임 시작시 inputManager update
		inputManager.Udate(); 

		sf::Event event; 
		while (r_window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				r_window->close(); 
			}
			//이벤트로 키 상태 확인. 
			inputManager.ProcessEvent(event); 
		}

		//0.1f 라는 값에서 실제 측정된 값으로 수정. 
		update(dt); 
		r_window->clear(); 
		render(*r_window); 
		r_window->display(); 
	}
}

bool Game2D::isKeyPressed()
{
	return false;
}

//26.01.08 
InputManager& Game2D::getInputManager()
{
	return inputManager; 
}

