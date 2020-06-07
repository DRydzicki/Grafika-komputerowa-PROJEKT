#include "Exc3.h"

namespace Exc3 {
	void DrawWindow()
	{
		Window window(1280, 768, "Project");
		ex1 = ex2 = false;
		window.RenderWindow(WindowContent);
	}

	void WindowContent(sf::RenderWindow& window)
	{
		sf::Vector2u windowSize = window.getSize();
		sf::Vector2f buttonSize = sf::Vector2f(windowSize.x * 0.20, windowSize.y * 0.05);
		sf::Vector2f inputSize = sf::Vector2f(windowSize.x * 0.08, windowSize.y * 0.03);

		sf::RectangleShape shape;
		shape.setSize(sf::Vector2f(windowSize.x * 0.7, windowSize.y * 0.9));
		shape.setPosition(sf::Vector2f(windowSize.x * 0.04, windowSize.y * 0.04));
		shape.setFillColor(sf::Color::Color(128, 128, 128));

		TextField button1;
		button1.setString("Bezier");
		button1.setOutline(2);
		button1.setSize(buttonSize);
		button1.setPosition(sf::Vector2f(shape.getSize().x + windowSize.x * 0.06 + button1.getGlobalBounds().width / 2, buttonSize.y + windowSize.y * 0.04));


		TextField button2;
		button2.setString("Hermit");
		button2.setOutline(2);
		button2.setSize(buttonSize);
		button2.setPosition(sf::Vector2f(shape.getSize().x + windowSize.x * 0.06 + button2.getGlobalBounds().width / 2, button1.getShapePosition().y + buttonSize.y + windowSize.y * 0.04));

		if (ex1)
			button1.setOutline(2, sf::Color::Red);
		else if (ex2)
			button2.setOutline(2, sf::Color::Red);

		button1.Draw(window);
		button2.Draw(window);

		shape.setFillColor(sf::Color::Black);
		window.draw(shape);

		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left) {
				if (button1.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
					ex1 = true;
					ex2 = false;
					points.clear();
				}
				if (button2.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
					ex2 = true;
					ex1 = false;
					points.clear();
				}
				if (ex1 == true && shape.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
					if (points.size() < 4) {
						points.push_back(mousePos);
					}
				}
				if (ex2 == true && shape.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
					if (points.size() < 4) {
						points.push_back(mousePos);
					}
				}
			}
		}

		if (ex1 == true) {
			for (int i = 0; i < points.size(); i++) {
				sf::CircleShape point(3);
				point.setFillColor(sf::Color::Green);
				point.setPosition(points[i].x,points[i].y);
				window.draw(point);
			}
			if (points.size() == 4) {
				Point p1(points[0]);
				Point p2;

				double precision = 100;
				double increase = 1.0 / precision;

				for (double i = 0; i <= 1; i += increase) {
					p2.x = (float)((pow(1 - i, 3) * points[0].x) + (3 * i * pow(1 - i, 2) * points[1].x) + (3 * pow(i, 2) * (1 - i) * points[2].x) + (pow(i, 3) * points[3].x));
					p2.y = (float)((pow(1 - i, 3) * points[0].y) + (3 * i * pow(1 - i, 2) * points[1].y) + (3 * pow(i, 2) * (1 - i) * points[2].y) + (pow(i, 3) * points[3].y));
					Line::DrawLine(p1, p2, window);
					p1 = p2;
				}
				
			}
		}

		else if (ex2 == true) {
			for (int i = 0; i < points.size(); i++) {
				sf::CircleShape point(3);
				point.setFillColor(sf::Color::Green);
				point.setPosition(points[i].x, points[i].y);
				window.draw(point);
			}
			if (points.size() == 4) {
				Point p1;
				Point p2;
				Point r1;
				Point r4;

				Line::DrawLineCustom(points[0].x, points[0].y, points[1].x, points[1].y, window, sf::Color::Green);
				Line::DrawLineCustom(points[2].x, points[2].y, points[3].x, points[3].y, window, sf::Color::Green);

				r1.x = points[1].x - points[0].x;
				r1.y = points[1].y - points[0].y;

				r4.x = points[3].x - points[2].x;
				r4.y = points[3].y - points[2].y;

				p1.x = points[0].x;
				p1.y = points[0].y;

				double precision = 100;
				double increase = 1.0 / precision;

				for (double i = 0; i <= 1; i += increase) {
					p2.x = (double) (((2*pow(i, 3)-(3*pow(i, 2))+1) * points[0].x) +
						((-2 * pow(i, 3) + 3 * pow(i, 2)) * points[2].x) +
						((pow(i, 3) - 2 * pow(i, 2) + i) * r1.x) +
						((pow(i, 3) - pow(i, 2)) * r4.x));

					p2.y = (double)(((2 * pow(i, 3) - (3 * pow(i, 2)) + 1) * points[0].y) +
						((-2 * pow(i, 3) + 3 * pow(i, 2)) * points[2].y) +
						((pow(i, 3) - 2 * pow(i, 2) + i) * r1.y) +
						((pow(i, 3) - pow(i, 2)) * r4.y));

					Line::DrawLine(p2, p1, window);
					p1 = p2;
				}
			}

		}

		window.display();
	}


}