#include "InputManager.hpp"

void InputManager::BindAction(const std::string& actionName, sf::Keyboard::Key key, 
	InputType type ) {
	actionBindings[actionName].push_back({ key, type }); 
}

void InputManager::ClearBindings()
{
	actionBindings.clear(); 
}

void InputManager::UnbindAction(const std::string& actionName)
{
	actionBindings.erase(actionName); 
}

// 26. 01.08 매 프레임 시작 시 호출 - 이전 프레임 상태 저장
void InputManager::Udate()
{
	previousKeyStates = currentKeyStates; 
}

//26.01.08 이벤트 처리 (옵션 - KeyPressed/Released를 이벤트로 감지하고 싶을 때)
void InputManager::ProcessEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed) {
		currentKeyStates[event.key.code] = true; 
	}
	else if (event.type == sf::Event::KeyReleased) {
		currentKeyStates[event.key.code] = false; 
	}
}

// 액션이 활성화되었는지 확인
bool InputManager::isActionActive(const std::string& actionName)
{
	if(actionBindings.find(actionName) == actionBindings.end()) return false;

	for (const auto& binding : actionBindings[actionName]) {
		bool isPressed = sf::Keyboard::isKeyPressed(binding.key); 
		bool wasPressed = previousKeyStates[binding.key]; 

		currentKeyStates[binding.key] = isPressed; 

		switch (binding.type) {
		case InputType::KeyHeld:
			if (isPressed) return true; 
			break; 
		case InputType::KeyPressed:
			if (isPressed && !wasPressed) return true; 
			break; 
		case InputType::KeyReleased:
			if (!isPressed && wasPressed) return true;
			break; 
		}
	}
	return false; 
}

// 축(Axis) 값 가져오기 (-1.0 ~ 1.0)
float InputManager::GetAxisValue(const std::string& axisName)
{
	float value = 0.0f;
	// Positive 방향 체크
	if (isActionActive(axisName + "_Positive"))
		value += 1.0f; 
	if (isActionActive(axisName + "_Negative"))
		value -= 1.0f; 

	return value;
}


//26.01.08 방향키와 ADWS키를 바인딩. 
void InputManager::setupInputBindings()
{
	//수평방향 이동. 
	BindAction("MoveHorizontal_Positive", sf::Keyboard::Key::D);
	BindAction("MoveHorizontal_Positive", sf::Keyboard::Key::Right); //방향키. 
	BindAction("MoveHorizontal_Negative", sf::Keyboard::Key::A);
	BindAction("MoveHorizontal_Negative", sf::Keyboard::Key::Left);

	//수직방향 이동. 
	BindAction("MoveVertical_Negative", sf::Keyboard::Key::W);
	BindAction("MoveVertical_Negative", sf::Keyboard::Key::Up);
	BindAction("MoveVertical_Positive", sf::Keyboard::Key::S);
	BindAction("MoveVertical_Positive", sf::Keyboard::Key::Down);

	//액션. 
	BindAction("Jump", sf::Keyboard::Key::Space, InputType::KeyPressed);
	BindAction("Attack", sf::Keyboard::Key::J, InputType::KeyPressed);
	BindAction("Dash", sf::Keyboard::Key::LShift, InputType::KeyHeld);
	BindAction("Pause", sf::Keyboard::Key::Escape, InputType::KeyPressed);

}