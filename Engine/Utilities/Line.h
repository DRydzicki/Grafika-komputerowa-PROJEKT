#pragma once
#include"Point.h"
#include<SFML/Graphics.hpp>

class Line
{
public:
    static void DrawLine(Point p1, Point p2, sf::RenderWindow& window, sf::Color color = sf::Color::Red) {
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(p1.x, p1.y), color),
            sf::Vertex(sf::Vector2f(p2.x, p2.y), color),
        };
        window.draw(line, 2, sf::Lines);
    }

    static void DrawLineCustom(int x1, int y1, int x2, int y2, sf::RenderWindow& window, sf::Color color = sf::Color::Red) {
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(x1,y1), color),
            sf::Vertex(sf::Vector2f(x2,y2), color)
        };
        window.draw(line, 2, sf::Lines);
    }
};

