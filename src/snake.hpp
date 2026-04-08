#pragma once
#include <random>
#include <SFML/Graphics.hpp>
#include <vector>

class Snake {
    public:
        Snake();
        int cols, lines, size, width, height, direction;
        sf::RenderWindow window;
        sf::Font f1;
        sf::Texture t1,t2,t3;
        sf::Sprite sp1,sp2,sp3;
        sf::Clock clock;
        std::mt19937 gen;
        std::random_device rd;

        enum class game_status {
            MENU,
            PAUSED,
            GAME_OVER,
            PLAYING
        };

        game_status status = {game_status::MENU};

        float timer, delay;

        void make_map();
        void run_game();
        void collision();
        void gen_fruit();
        void game_over();
        void menu();
        void paused();
};