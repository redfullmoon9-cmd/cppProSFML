#pragma once 
#include <SFML/Window.hpp>
#include <map>
#include <unordered_map>
/* 1.08 신규작성. 키보드 이벤트 액션 바인딩 방식으로 수정. */

enum class InputType {
	KeyPressed, //한번 눌렀을때 
	KeyReleased, //눌렀다 떼었을때
	KeyHeld //누르고 있는..
};


struct InputBinding {
	sf::Keyboard::Key key; 
	InputType type; 
};

//test 
class InputManager {
private:
	std::map<std::string, std::vector<InputBinding>> actionBindings;
	std::unordered_map<sf::Keyboard::Key, bool> currentKeyStates; 
	std::unordered_map<sf::Keyboard::Key, bool> previousKeyStates; 
public: 
	InputManager()=default; 
	void BindAction(const std::string& actionName, sf::Keyboard::Key key, InputType type=InputType::KeyHeld);
	void Udate(); 
	void ProcessEvent(const sf::Event& event); //keyPressed와 Release이벤트 감지 
	bool isActionActive(const std::string& actionName); 
	float GetAxisValue(const std::string& axisName); 
	void ClearBindings(); 
	void UnbindAction(const std::string& actionName); 
	void setupInputBindings(); 

};