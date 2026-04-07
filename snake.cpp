#include "snake.hpp"

sf::Vector2i snake_body[100];
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

void Snake::make_map() {
    for (int c{}; c < cols; c++)
    {
        for (int l{}; l < lines; l++)
        {
            sp1.setPosition(c * size, l * size);
            window.draw(sp1);
        }
    }
}

void Snake::collision() {
    // aqui a gente só mexe a cabeça (lá ele)
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        direction = 0;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        direction = 1;      
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        direction = 2;      
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        direction = 3;      
    }

    switch (direction) {
        case 0:
            snake_body[0].x +=1;
            break;
        case 1:
            snake_body[0].x -=1;
            break;
        case 2:
            snake_body[0].y -=1;
            break;
        case 3:
            snake_body[0].y +=1;
            break;
    }

}

void Snake::run_game() {
    while (window.isOpen())
    {

        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if(timer > delay) {
            timer = 0;
            collision();
        }

        window.clear();
        make_map();

        for (int i{}; i < num; i++)
        {
            sp2.setPosition(size * snake_body[i].x, size * snake_body[i].y);
            window.draw(sp2);
        }

        window.display();

    }
}