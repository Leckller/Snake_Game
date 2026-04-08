#include "snake.hpp"

std::vector<sf::Vector2i> snake_body;
sf::Vector2i fruit;

Snake::Snake()
{
    cols = 20;
    lines = 13;
    size = 64;
    width = size * cols;
    height = size * lines;
    direction = 0;
    timer = 0.f;
    delay = 0.1f;
    gen = std::mt19937(rd());

    window.create(sf::VideoMode(width, height), "Snake Game", sf::Style::Titlebar | sf::Style::Close);

    t1.loadFromFile("./src/assets/sprites/bg.png");
    t2.loadFromFile("./src/assets/sprites/snake.png");
    t3.loadFromFile("./src/assets/sprites/fruta.png");

    f1.loadFromFile("./src/assets/fonts/arial.ttf");

    sp1.setTexture(t1);
    sp2.setTexture(t2);
    sp3.setTexture(t3);

    start_btn.setFillColor(sf::Color::White);
    start_btn.setSize(sf::Vector2f(200.f, 100.f));
    start_btn.setPosition((window.getSize().x / 2) - (start_btn.getSize().x / 2), (window.getSize().y / 2) - (start_btn.getSize().y / 2));

    start_text.setFont(f1);
    start_text.setString("Iniciar");
    start_text.setFillColor(sf::Color::Black);
    sf::FloatRect text_bounds = start_text.getLocalBounds();
    start_text.setOrigin(
        text_bounds.left + (text_bounds.width / 2),
        text_bounds.top + (text_bounds.height / 2)
    );
    start_text.setPosition(start_btn.getPosition().x + (start_btn.getSize().x / 2), start_btn.getPosition().y + (start_btn.getSize().y / 2));

}

void Snake::make_map()
{
    for (int c{}; c < cols; c++)
    {
        for (int l{}; l < lines; l++)
        {
            sp1.setPosition(c * size, l * size);
            window.draw(sp1);
        }
    }
}

void Snake::gen_fruit()
{
    std::uniform_int_distribution<> distribCols(0, cols - 1);
    std::uniform_int_distribution<> distribLines(0, lines - 1);

    // verificação para não gerar a fruta dentro do body da snake
    bool valid = false;
    while (!valid)
    {
        valid = true;
        fruit.x = distribCols(gen);
        fruit.y = distribLines(gen);

        for (size_t i = 0; i < snake_body.size(); i++)
        {
            if (snake_body[i].x == fruit.x && snake_body[i].y == fruit.y)
            {
                valid = false;
                break;
            }
        }
    }

    sp3.setPosition(fruit.x * size, fruit.y * size);
}

void Snake::collision()
{
    // loop p acompanhar a cabeça ( aqui eu atualizo a posição de cada parte do corpo para a posição da parte à frente)
    for (int i = snake_body.size() - 1; i > 0; i--)
    {
        snake_body[i].x = snake_body[i - 1].x;
        snake_body[i].y = snake_body[i - 1].y;
    }

    // aqui a gente só mexe a cabeça (lá ele)
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && direction != 1)
    {
        direction = 0;
    }

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && direction != 0)
    {
        direction = 1;
    }

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && direction != 3)
    {
        direction = 2;
    }

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && direction != 2)
    {
        direction = 3;
    }

    switch (direction)
    {
    case 0:
        snake_body[0].x += 1;
        break;
    case 1:
        snake_body[0].x -= 1;
        break;
    case 2:
        snake_body[0].y -= 1;
        break;
    case 3:
        snake_body[0].y += 1;
        break;
    }

    // aq valida se colidiu com a fruta
    if (fruit.x == snake_body[0].x && fruit.y == snake_body[0].y)
    {
        gen_fruit();
        snake_body.push_back(snake_body.back());
    }

    // colisão nas extremidades
    if (snake_body[0].x > cols - 1)
    {
        snake_body[0].x = 0;
    }
    if (snake_body[0].x < 0)
    {
        snake_body[0].x = cols - 1;
    }

    if (snake_body[0].y > lines - 1)
    {
        snake_body[0].y = 0;
    }

    if (snake_body[0].y < 0)
    {
        snake_body[0].y = lines - 1;
    }
}

void Snake::game_over()
{
}

void Snake::paused() {

};

void Snake::menu()
{
}

void Snake::run_game()
{
    snake_body.push_back({5, 5});
    snake_body.push_back({4, 5});
    snake_body.push_back({3, 5});
    snake_body.push_back({2, 5});
    gen_fruit();

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        switch (status)
        {
        case game_status::PLAYING:
        {

            if (timer > delay)
            {
                timer = 0;
                collision();
            }

            make_map();
            window.draw(sp3);

            for (size_t i{}; i < snake_body.size(); i++)
            {
                sp2.setPosition(size * snake_body[i].x, size * snake_body[i].y);
                window.draw(sp2);
            }

            break;
        }
        case game_status::PAUSED:
        {
            paused();
            break;
        }
        case game_status::MENU:
        {
            menu();
            break;
        }
        case game_status::GAME_OVER:
        {
            game_over();
            break;
        }
        }
        window.display();
    }
}