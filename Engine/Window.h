#pragma once
#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
class Window
{
public:
	int width, height;
	sf::String title;

	Window(int width, int height, sf::String title);

	void RenderWindow(void(*fun)(sf::RenderWindow& ));
};

