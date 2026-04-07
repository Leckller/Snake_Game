#include "snake.hpp"

sf::Vector2i snake[100];
sf::Vector2i fruit;

Snake::Snake(){
    cols = 20;
    lines= 13;
    size = 64;
    width = size * cols;
    height = size * lines;
    direction = 0;
    num = 4;
    timer = 0.f;
    delay = 0.1f;

    window.create(sf::VideoMode(width, height), "Snake Game", sf::Style::Titlebar | sf::Style::Close);

    t1.loadFromFile("./bg.png");
    t2.loadFromFile("./snake.png");
    t3.loadFromFile("./fruta.png");

    sp1.setTexture(t1);
    sp2.setTexture(t2);
    sp3.setTexture(t3);
}

void Snake::run_game() {
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        for (int c{}; c < cols; c++)
        {
            for (int l{}; l < lines; l++)
            {
                sp1.setPosition(c * size, l * size);
                window.draw(sp1);
            }
        }

        window.display();

    }
}