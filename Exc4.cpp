#include "Exc4.h"

namespace Exc4 {

	void DrawWindow()
	{
		Window window(1280, 768, "Project");
		ex1 = ex2 = ex3 = ex4 = done = false;
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
		button1.setString("Z ktorej strony");
		button1.setOutline(2);
		button1.setSize(buttonSize);
		button1.setPosition(sf::Vector2f(shape.getSize().x + windowSize.x * 0.06 + button1.getGlobalBounds().width / 2, buttonSize.y + windowSize.y * 0.04));


		TextField button2;
		button2.setString("Dwa punkty");
		button2.setOutline(2);
		button2.setSize(buttonSize);
		button2.setPosition(sf::Vector2f(shape.getSize().x + windowSize.x * 0.06 + button2.getGlobalBounds().width / 2, button1.getShapePosition().y + buttonSize.y + windowSize.y * 0.04));

		TextField button3;
		button3.setString("Przecinanie");
		button3.setOutline(2);
		button3.setSize(buttonSize);
		button3.setPosition(sf::Vector2f(shape.getSize().x + windowSize.x * 0.06 + button3.getGlobalBounds().width / 2, button2.getShapePosition().y + buttonSize.y + windowSize.y * 0.04));

		TextField button4;
		button4.setString("Wielokat");
		button4.setOutline(2);
		button4.setSize(buttonSize);
		button4.setPosition(sf::Vector2f(shape.getSize().x + windowSize.x * 0.06 + button4.getGlobalBounds().width / 2, button3.getShapePosition().y + buttonSize.y + windowSize.y * 0.04));


		TextField result;
		result.setOutline(1);
		result.setSize(inputSize);
		result.setPosition(sf::Vector2f(shape.getSize().x + windowSize.x * 0.06 + result.getGlobalBounds().width / 2, button4.getShapePosition().y + inputSize.y + windowSize.y * 0.1));

		TextField tDone;
		tDone.setOutline(1);
		tDone.setSize(inputSize);
		tDone.setPosition(sf::Vector2f(shape.getSize().x + windowSize.x * 0.06 + tDone.getGlobalBounds().width / 2, result.getShapePosition().y + inputSize.y + windowSize.y * 0.1));

		if (ex1)
			button1.setOutline(2, sf::Color::Red);
		else if (ex2)
			button2.setOutline(2, sf::Color::Red);
		else if (ex3)
			button3.setOutline(2, sf::Color::Red);
		else if (ex4)
			button4.setOutline(2, sf::Color::Red);

		button1.Draw(window);
		button2.Draw(window);
		button3.Draw(window);
		button4.Draw(window);
		

		shape.setFillColor(sf::Color::Black);
		window.draw(shape);

		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left) {
				if (button1.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
					ex1 = true;
					ex2 = ex3 = ex4 = false;
					points.clear();
				}
				if (button2.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
					ex2 = true;
					ex1 = ex3 = ex4 = false;
					points.clear();
				}
				if (button3.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
					ex3 = true;
					ex2 = ex1 = ex4 = false;
					points.clear();
				}
				if (button4.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
					ex4 = true;
					ex2 = ex3 = ex1 = false;
					points.clear();
					done = false;
				}
				if (done == false && tDone.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
					done = true;
				}
				if (ex1 == true && shape.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
					if (points.size() < 3) {
						points.push_back(mousePos);
					}
				}
				if (ex2 == true && shape.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
					if (points.size() < 4) {
						points.push_back(mousePos);
					}
				}
				if (ex3 == true && shape.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
					if (points.size() < 4) {
						points.push_back(mousePos);
					}
				}
				if (ex4 == true && shape.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
					if (done == false) {
						points.push_back(mousePos);
					}
				}

			}
		}


		if (ex1 == true) {
			for (int i = 0; i < points.size(); i++) {
				sf::CircleShape point(3);
				point.setFillColor(sf::Color::Green);
				point.setOrigin(sf::Vector2f(point.getLocalBounds().width / 2, point.getLocalBounds().height / 2));
				point.setPosition(points[i].x, points[i].y);
				window.draw(point);
			}
			if (points.size() == 3) {
				Point p1(points[0]);
				Point p2(points[1]);
				Point p3(points[2]);

				Line::DrawLine(p1, p2, window);
				int s = side(p1, p2, p3);

				result.setCharacterSize(10);
				
				if (s == 0)
					result.setString("NA PROSTEJ");
				else if (s == -1)
					result.setString("NA LEWO");
				else if (s == 1)
					result.setString("NA PRAWO");
				
				
				result.Draw(window);

			}
		}
		else if (ex2 == true) {
			for (int i = 0; i < points.size(); i++) {
				sf::CircleShape point(3);
				point.setFillColor(sf::Color::Green);
				point.setOrigin(sf::Vector2f(point.getLocalBounds().width / 2, point.getLocalBounds().height / 2));
				point.setPosition(points[i].x, points[i].y);
				window.draw(point);
			}
			if (points.size() == 4) {
				Point p1(points[0]);
				Point p2(points[1]);
				Point p3(points[2]);
				Point p4(points[3]);
				Line::DrawLine(p1, p2, window);
				result.setCharacterSize(10);
				bool s = sameSide(p1, p2, p3, p4);
				if(s==true)
					result.setString("TA SAMA");
				else
					result.setString("ROZNA");

				result.Draw(window);
			}
		}
		else if (ex3 == true) {
			for (int i = 0; i < points.size(); i++) {
				sf::CircleShape point(3);
				point.setFillColor(sf::Color::Green);
				point.setOrigin(sf::Vector2f(point.getLocalBounds().width / 2, point.getLocalBounds().height / 2));
				point.setPosition(points[i].x, points[i].y);
				window.draw(point);
			}
			if (points.size() == 4) {
				Point p1(points[0]);
				Point p2(points[1]);
				Point p3(points[2]);
				Point p4(points[3]);
				Line::DrawLine(p1, p2, window);
				Line::DrawLine(p3, p4, window, sf::Color::Green);
				result.setCharacterSize(10);
				bool s = intersect(p1, p2, p3, p4);
				if (s == true)
					result.setString("przecina");
				else
					result.setString("nie przecina");

				result.Draw(window);
			}
		}
		else if (ex4 == true) {
			for (int i = 0; i < points.size(); i++) {
				sf::CircleShape point(3);
				point.setFillColor(sf::Color::Green);
				point.setOrigin(sf::Vector2f(point.getLocalBounds().width / 2, point.getLocalBounds().height / 2));
				point.setPosition(points[i].x, points[i].y);
				window.draw(point);
			}
			tDone.setCharacterSize(10);
			tDone.setString("DONE");
			tDone.Draw(window);
			
			if (done == true) {
				
				Point p0(shape.getPosition().x, shape.getPosition().y);
				Point pEnd(points[points.size() - 1]);
				Line::DrawLine(p0, pEnd, window, sf::Color::Green);
				int calc = 0;
				tDone.setOutline(2, sf::Color::Red);
				
				for (int i = 0; i < points.size()-1; i++) {
					bool s;
					if (i == points.size()-2) {
						Point p1(points[0]);
						Point p2(points[i]);
						Line::DrawLine(p1, p2, window);
						s = intersect(p0, pEnd, p1, p2);
					}
					else {
						Point p1(points[i]);
						Point p2(points[i + 1]);
						Line::DrawLine(p1, p2, window);
						s = intersect(p0, pEnd, p1, p2);
					}
					if (s == true)
						calc++;
				}
				result.setCharacterSize(10);
				if (calc % 2 == 0)
					result.setString(std::to_string(calc) + " POZA");
				else 
					result.setString(std::to_string(calc) + " WEWNATRZ");
				result.Draw(window);
			}
		}
		window.display();
	}

	int side(Point a, Point b, Point c) {
		float determinant = a.x * b.y * 1 + a.y * 1 * c.x + 1 * b.x * c.y - 1 * b.y * c.x - a.x * 1 * c.y - a.y * b.x * 1;

		if (determinant > 0) return 1;
		else if (determinant < 0) return -1;
		return 0;
	}

	bool sameSide(Point a, Point b, Point c, Point d) {
		int f1 = side(a, b, c);
		int f2 = side(a, b, d);

		if (sign(f1) == sign(f2)) return true;
		return false;
	}

	bool intersect(Point a, Point b, Point c, Point d) {
		bool f1 = sameSide(a, b, c, d);
		bool f2 = sameSide(c, d, a, b);

		if (f1 == false && f2 == false) return true;
		return false;
	}

	int sign(int x) {
		return (x > 0) - (x < 0);
	}
}