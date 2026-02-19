
#pragma once
#include "Game2D.hpp"
#include <vector>
#include <array>
#include <random>

//그려질 박스의 모양과 속도를 같이 가지고
struct Box {
	sf::RectangleShape shape; 
	sf::Vector2f velocity; 
};

class DrawTest :public Game2D {
private: 
	//랜덤관련 한번만 초기화, 사용할 때 꺼내서.  
	std::random_device rd;
	std::mt19937 gen{ rd() };
	std::uniform_int_distribution<int> disX{ 1, 900 };
	std::uniform_int_distribution<int> disY{ 1, 600 };
	std::uniform_int_distribution<int> disC{ 1, 255};

	std::uniform_real_distribution<float> disSpeed{ -50.f, 50.f }; 
	

	std::vector<Box> boxes; 
	float m_xPos =0.0f; 
	float m_direction=1.0f; 


public: 
	using Game2D::Game2D; 
	DrawTest();
	~DrawTest() {};

	void update(float dt) override;
	void render(sf::RenderWindow& r_window) override; 

	void drawShape(); 
};
