#include "DrawTest3.hpp"

DrawTest3::DrawTest3()
{
    playerPosition = sf::Vector2f{10.0f, 10.0f};
    playerColor = sf::Color{238, 108, 77, 255};
    player.setSize(sf::Vector2f(playerSize, playerSize));
    player.setFillColor(playerColor);

    enemyPositions = new sf::Vector2f[ENEMYCNT];
    enemyColor = sf::Color{200, 150, 255, 255};

    for (int i = 0; i < ENEMYCNT; i++)
    {
        enemyPositions[i].x = SCREEN_WIDTH - 100;
        enemyPositions[i].y = static_cast<float>(rand() % SCREEN_HEIGHT);

        enemies[i] = sf::CircleShape{enemySize};
        enemies[i].setFillColor(enemyColor);
        enemies[i].setOutlineColor(sf::Color::Red);
        enemies[i].setOutlineThickness(1.0f);
    }
}

DrawTest3::~DrawTest3()
{
    delete[] enemyPositions;
}

void DrawTest3::update(float dt)
{
    UpdatePlayerPosition(playerPosition);
    player.setPosition(playerPosition);

    UpdateEnemiesPosition(enemySpeed, enemyPositions, ENEMYCNT, playerPosition);
    for (int i = 0; i < ENEMYCNT; i++)
    {
        enemies[i].setPosition(enemyPositions[i]);
    }
}

void DrawTest3::render(sf::RenderWindow &r_window)
{
    r_window.draw(player);
    for (int i = 0; i < ENEMYCNT; i++)
    {
        r_window.draw(enemies[i]);
    }
}

void DrawTest3::UpdatePlayerPosition(sf::Vector2f &playerPosition)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        playerPosition.x -= playerSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        playerPosition.x += playerSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        playerPosition.y -= playerSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        playerPosition.y += playerSpeed;
    }
}

void DrawTest3::UpdateEnemiesPosition(float enemySpeed, sf::Vector2f *enemyPositions,
                                      int enemyCount, sf::Vector2f playerPosition)
{
    for (int i = 0; i < enemyCount; i++)
    {
        float enemyToPlayerX = playerPosition.x - enemyPositions[i].x;
        float enemyToPlayerY = playerPosition.y - enemyPositions[i].y;

        float length = std::sqrt(enemyToPlayerX * enemyToPlayerX + enemyToPlayerY * enemyToPlayerY);

        // 백터의 정규화 과정 모든 벡터를 방향을 유지 한 상태로 1로 만들어 준다.
        enemyToPlayerX /= length;
        enemyToPlayerY /= length;

        enemyPositions[i].x += enemyToPlayerX * enemySpeed;
        enemyPositions[i].y += enemyToPlayerY * enemySpeed;
    }
}
