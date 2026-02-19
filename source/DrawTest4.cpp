#include "DrawTest4.hpp"

DrawTest4::DrawTest4()
{
	//inputManager.setupInputBindings(); 
}

DrawTest4::~DrawTest4()
{
}

void DrawTest4::update(float dt)
{
	//inputProcess(dt); 

}

void DrawTest4::render(sf::RenderWindow window) {

}

//InputManager& DrawTest4::getInputManager()
//{
//	return inputManager; 
//}

//void DrawTest4::inputProcess(float deltaTime)
//{
//	sf::Vector2f direction{ 0.f, 0.f }; 
//	direction.x = inputManager.GetAxisValue("MoveHorizontal");
//	direction.y = inputManager.GetAxisValue("MoveVertical");
//
//	if (inputManager.isActionActive("MoveHorizontal_Positive")) {
//		std::cout << "press D or right" << std::endl;
//	}
//	if (inputManager.isActionActive("MoveHorizontal_Negative")) {
//		std::cout << "press A or Left" << std::endl;
//	}
//	if (inputManager.isActionActive("MoveVertical_Negative")) {
//		std::cout << "Press W or up " <<std::endl; 
//	}
//
//	//점프 처리. 
//	if (inputManager.isActionActive("Jump")) { //space
//		std::cout << "jum .. p " << std::endl;
//	}
//
//	// 공격처리. 
//	if (inputManager.isActionActive("Attack")) { //j
//		std::cout << " attack " << std::endl;
//	}
//
//
//}
