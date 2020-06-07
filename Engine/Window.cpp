#include "Window.h"

Window::Window(int width, int height, sf::String title)
{
	this->width = width;
	this->height = height;
	this->title = title;
}

void Window::RenderWindow(void (*fun) (sf::RenderWindow& ))
{
	sf::RenderWindow window(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);


	sf::Clock clock;
	double t = 0.0;
	double dt = 1 / 120;

	while (window.isOpen()) {
		double time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		t += time;

		window.clear(sf::Color::White);
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		fun(window);


	}
	
}
