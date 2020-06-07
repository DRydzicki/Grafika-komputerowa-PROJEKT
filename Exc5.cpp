#include "Exc5.h"

namespace Exc5 {
	void DrawWindow()
	{
		Window window(1280, 768, "Project");
		ex1 = ex2 = ex3 = false;
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
		button1.setString("Translacja");
		button1.setOutline(2);
		button1.setSize(buttonSize);
		button1.setPosition(sf::Vector2f(shape.getSize().x + windowSize.x * 0.06 + button1.getGlobalBounds().width / 2, buttonSize.y + windowSize.y * 0.04));


		TextField button2;
		button2.setString("Rotacja");
		button2.setOutline(2);
		button2.setSize(buttonSize);
		button2.setPosition(sf::Vector2f(shape.getSize().x + windowSize.x * 0.06 + button2.getGlobalBounds().width / 2, button1.getShapePosition().y + buttonSize.y + windowSize.y * 0.04));

		TextField button3;
		button3.setString("Skalowanie");
		button3.setOutline(2);
		button3.setSize(buttonSize);
		button3.setPosition(sf::Vector2f(shape.getSize().x + windowSize.x * 0.06 + button3.getGlobalBounds().width / 2, button2.getShapePosition().y + buttonSize.y + windowSize.y * 0.04));

		if (ex1)
			button1.setOutline(2, sf::Color::Red);
		else if (ex2)
			button2.setOutline(2, sf::Color::Red);
		else if (ex3)
			button3.setOutline(2, sf::Color::Red);

		button1.Draw(window);
		button2.Draw(window);
		button3.Draw(window);

		shape.setFillColor(sf::Color::Black);
		window.draw(shape);

		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left) {
				if (button1.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
					ex1 = true;
					ex2 = ex3 = false;
				}
				if (button2.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
					ex2 = true;
					ex1 = ex3 = false;
				}
				if (button3.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
					ex3 = true;
					ex2 = ex1 = false;
				}
			}
		}

		if (ex1 == true) {
			std::vector<std::vector<double>> matrix;
			matrix.resize(3, std::vector<double>(3, 0));
			matrix[0][0] = 1; matrix[0][2] = 100;
			matrix[1][1] = 1; matrix[1][2] = 100;
			matrix[2][2] = 1;
			double R = 200, N = 5, Z = 10;
			double alpha = 0;
			double dalpha = 2 * PI / N;
			double dR = R / (N * Z);
			R = 0;

			std::vector<std::vector<double>> points2;
			points2.resize((int)N * Z + 1, std::vector<double>(3, 0));

			for (int i = 0; i < N * Z; i++) {
				points2[i][0] = (int)(R * cos(alpha)) + shape.getSize().x / 2;
				points2[i][1] = (int)(R * sin(alpha)) + shape.getSize().y / 2;
				points2[i][2] = 1;
				alpha += dalpha;
				R += dR;
			}

			for (int i = 0; i <= (N * Z) - 2; i++) {
				Line::DrawLineCustom(points2[i][0], points2[i][1], points2[i + 1][0], points2[i + 1][1], window);
			}

			points2 = MyVector::multiply(matrix, points2);

			for (int i = 0; i <= (N * Z) - 2; i++) {
				Line::DrawLineCustom(points2[i][0], points2[i][1], points2[i + 1][0], points2[i + 1][1], window);
			}
		}
		else if (ex2 == true) {
			std::vector<std::vector<double>> matrix;
			matrix.resize(3, std::vector<double>(3, 0));
			matrix[0][0] = cos(5 * (PI / 100)); matrix[0][1] = sin(5 * (PI / 100));
			matrix[1][0] = -sin(5 * (PI / 100)); matrix[1][1] = cos(5 * (PI / 100));
			matrix[2][2] = -1;
			double R = 200, N = 5, Z = 10;
			double alpha = 0;
			double dalpha = 2 * PI / N;
			double dR = R / (N * Z);
			R = 0;

			std::vector<std::vector<double>> points2;
			points2.resize((int)N * Z + 1, std::vector<double>(3, 0));

			for (int i = 0; i < N * Z; i++) {
				points2[i][0] = (int)(R * cos(alpha)) + shape.getSize().x / 2;
				points2[i][1] = (int)(R * sin(alpha)) + shape.getSize().y / 2;
				points2[i][2] = 1;
				alpha += dalpha;
				R += dR;
			}

			for (int i = 0; i <= (N * Z) - 2; i++) {
				Line::DrawLineCustom(points2[i][0], points2[i][1], points2[i + 1][0], points2[i + 1][1], window);
			}

			points2 = MyVector::multiply(matrix, points2);

			for (int i = 0; i <= (N * Z) - 2; i++) {
				Line::DrawLineCustom(points2[i][0], points2[i][1], points2[i + 1][0], points2[i + 1][1], window);
			}
		}
		else if (ex3 == true) {
			std::vector<std::vector<double>> matrix;
			matrix.resize(3, std::vector<double>(3, 0));
			matrix[0][0] = 1.3;
			matrix[1][1] = 1.3;
			matrix[2][2] = 1;
			double R = 200, N = 5, Z = 10;
			double alpha = 0;
			double dalpha = 2 * PI / N;
			double dR = R / (N * Z);
			R = 0;

			std::vector<std::vector<double>> points2;
			points2.resize((int)N * Z + 1, std::vector<double>(3, 0));

			for (int i = 0; i < N * Z; i++) {
				points2[i][0] = (int)(R * cos(alpha)) + shape.getSize().x / 2;
				points2[i][1] = (int)(R * sin(alpha)) + shape.getSize().y / 2;
				points2[i][2] = 1;
				alpha += dalpha;
				R += dR;
			}

			for (int i = 0; i <= (N * Z) - 2; i++) {
				Line::DrawLineCustom(points2[i][0], points2[i][1], points2[i + 1][0], points2[i + 1][1], window);
			}

			points2 = MyVector::multiply(matrix, points2);

			for (int i = 0; i <= (N * Z) - 2; i++) {
				Line::DrawLineCustom(points2[i][0], points2[i][1], points2[i + 1][0], points2[i + 1][1], window);
			}
		}


		window.display();
	}


}

