#include "DrawTest1.hpp"
#include <iostream>
#include <random>

DrawTest::DrawTest()
{
    for (int i = 0; i < 30; i++)
    {
        int ix = disX(gen);
        int iy = disY(gen);

        Box box;
        box.shape.setSize(sf::Vector2f{50.0f, 50.0f});
        box.shape.setFillColor(sf::Color(disC(gen), disC(gen), disC(gen)));
        box.shape.setPosition(static_cast<float>(ix), static_cast<float>(iy));
        box.velocity.x = disSpeed(gen);
        box.velocity.y = disSpeed(gen);

        boxes.push_back(box);
    }
}

void DrawTest::update(float dt)
{
    for (auto &box : boxes)
    {
        box.shape.move(box.velocity * dt);
        sf::Vector2f pos = box.shape.getPosition();

        if (pos.x < 0 || pos.x > 1024 - 50)
        {
            box.velocity.x *= -1.f;
        }
        if (pos.y < 0 || pos.y > 768 - 50)
        {
            box.velocity.y *= -1.f;
        }
    }
}

void DrawTest::render(sf::RenderWindow &r_window)
{
    for (auto &box : boxes)
    {
        r_window.draw(box.shape);
    }
}

void DrawTest::drawShape()
{
    /*
    m_rect.setSize({ 100.0f, 50.0f });
    m_rect.setFillColor(sf::Color::Red);

    m_ball.setRadius(30.0f);
    m_ball.setFillColor(sf::Color::Blue);
    m_ball.setPosition(150.0f, 150.0f); */
}