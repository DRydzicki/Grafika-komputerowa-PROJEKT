#include"Exc1.h"

void Exc1::DrawWindow() {
    Window window(1280, 768, "Project");
    ex1 = ex2 = ex3 = ex4 = ex5 = isNSelected = isRSelected = isZSelected = false;
    window.RenderWindow(WindowContent);
}

void Exc1::WindowContent(sf::RenderWindow& window) {
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2f buttonSize = sf::Vector2f(windowSize.x * 0.20, windowSize.y * 0.05);
    sf::Vector2f inputSize = sf::Vector2f(windowSize.x * 0.08, windowSize.y * 0.03);

    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(windowSize.x * 0.7, windowSize.y * 0.9));
    shape.setPosition(sf::Vector2f(windowSize.x * 0.04, windowSize.y * 0.04));
    shape.setFillColor(sf::Color::Color(128, 128, 128));

    TextField button1;
    button1.setString("ex. 1: 1.2a");
    button1.setOutline(2);
    button1.setSize(buttonSize);
    button1.setPosition(sf::Vector2f(shape.getSize().x + windowSize.x * 0.06 + button1.getGlobalBounds().width / 2, buttonSize.y + windowSize.y * 0.04));

    TextField button2;
    button2.setString("ex. 2: 1.2b");
    button2.setOutline(2);
    button2.setSize(buttonSize);
    button2.setPosition(sf::Vector2f(shape.getSize().x + windowSize.x * 0.06 + button2.getGlobalBounds().width / 2, button1.getShapePosition().y + buttonSize.y + windowSize.y * 0.04));

    TextField button3;
    button3.setString("ex. 3: 1.4");
    button3.setOutline(2);
    button3.setSize(buttonSize);
    button3.setPosition(sf::Vector2f(shape.getSize().x + windowSize.x * 0.06 + button3.getGlobalBounds().width / 2, button2.getShapePosition().y + buttonSize.y + windowSize.y * 0.04));

    TextField button4;
    button4.setString("ex. 4: 1.6");
    button4.setOutline(2);
    button4.setSize(buttonSize);
    button4.setPosition(sf::Vector2f(shape.getSize().x + windowSize.x * 0.06 + button4.getGlobalBounds().width / 2, button3.getShapePosition().y + buttonSize.y + windowSize.y * 0.04));

    TextField button5;
    button5.setString("ex. 5: 2.2a");
    button5.setOutline(2);
    button5.setSize(buttonSize);
    button5.setPosition(sf::Vector2f(shape.getSize().x + windowSize.x * 0.06 + button5.getGlobalBounds().width / 2, button4.getShapePosition().y + buttonSize.y + windowSize.y * 0.04));

    TextField inputN;
    inputN.setOutline(1);
    inputN.setSize(inputSize);
    inputN.setPosition(sf::Vector2f(shape.getSize().x + windowSize.x * 0.06 + inputN.getGlobalBounds().width / 2, button5.getShapePosition().y + inputSize.y + windowSize.y * 0.1));

    sf::Text textN;
    textN.setString("N:");
    textN.setFont(Resources::get().fontHolder.get("arial"));
    textN.setCharacterSize(14);
    textN.setFillColor(sf::Color::Black);
    textN.setPosition(sf::Vector2f(inputN.getShapePosition().x - 1.5 * textN.getGlobalBounds().width, inputN.getShapePosition().y));
    window.draw(textN);

    TextField inputR;
    inputR.setOutline(1);
    inputR.setSize(inputSize);
    inputR.setPosition(sf::Vector2f(shape.getSize().x + windowSize.x * 0.06 + inputR.getGlobalBounds().width / 2, inputN.getShapePosition().y + inputSize.y + windowSize.y * 0.04));

    sf::Text textR;
    textR.setString("R:");
    textR.setFont(Resources::get().fontHolder.get("arial"));
    textR.setCharacterSize(14);
    textR.setFillColor(sf::Color::Black);
    textR.setPosition(sf::Vector2f(inputR.getShapePosition().x - 1.5 * textR.getGlobalBounds().width, inputR.getShapePosition().y));
    window.draw(textR);

    TextField inputZ;
    inputZ.setOutline(1);
    inputZ.setSize(inputSize);
    inputZ.setPosition(sf::Vector2f(shape.getSize().x + windowSize.x * 0.06 + inputZ.getGlobalBounds().width / 2, inputR.getShapePosition().y + inputSize.y + windowSize.y * 0.04));

    sf::Text textZ;
    textZ.setString("Z:");
    textZ.setFont(Resources::get().fontHolder.get("arial"));
    textZ.setCharacterSize(14);
    textZ.setFillColor(sf::Color::Black);
    textZ.setPosition(sf::Vector2f(inputZ.getShapePosition().x - 1.5 * textZ.getGlobalBounds().width, inputZ.getShapePosition().y));
    window.draw(textZ);

    if (ex1)
        button1.setOutline(2, sf::Color::Red);
    else if (ex2)
        button2.setOutline(2, sf::Color::Red);
    else if (ex3)
        button3.setOutline(2, sf::Color::Red);
    else if (ex4)
        button4.setOutline(2, sf::Color::Red);
    else if (ex5)
        button5.setOutline(2, sf::Color::Red);


    button1.Draw(window);
    button2.Draw(window);
    button3.Draw(window);
    button4.Draw(window);
    button5.Draw(window);


    shape.setFillColor(sf::Color::Black);
    window.draw(shape);

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left) {
            if (button1.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                ex1 = true;
                ex2 = ex3 = ex4 = ex5 = false;
            }
            if (button2.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                ex2 = true;
                ex1 = ex3 = ex4 = ex5 = false;
            }
            if (button3.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                ex3 = true;
                ex2 = ex1 = ex4 = ex5 = false;
            }
            if (button4.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                ex4 = true;
                ex2 = ex3 = ex1 = ex5 = false;
            }
            if (button5.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                ex5 = true;
                ex2 = ex3 = ex4 = ex1 = false;
            }
            if (inputN.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                isNSelected = !isNSelected;
                isRSelected = false;
                isZSelected = false;
            }
            if (inputR.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                isRSelected = !isRSelected;
                isNSelected = false;
                isZSelected = false;
            }
            if (inputZ.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                isZSelected = !isZSelected;
                isRSelected = false;
                isNSelected = false;
            }
        }
        if (event.type == sf::Event::TextEntered) {
            if (isNSelected && event.text.unicode >= 48 && event.text.unicode <= 57)
                tempN += event.text.unicode;
            else if (isNSelected && event.text.unicode == 8 && tempN.length() > 0)
                tempN.erase(tempN.length() - 1);

            if (isRSelected && event.text.unicode >= 48 && event.text.unicode <= 57)
                tempR += event.text.unicode;
            else if (isRSelected && event.text.unicode == 8 && tempR.length() > 0)
                tempR.erase(tempR.length() - 1);

            if (isZSelected && event.text.unicode >= 48 && event.text.unicode <= 57)
                tempZ += event.text.unicode;
            else if (isZSelected && event.text.unicode == 8 && tempZ.length() > 0)
                tempZ.erase(tempZ.length() - 1);
        }
    }
    inputN.setCharacterSize(10);
    inputN.setString(tempN);
    inputN.alignCenter();
    if (isNSelected)
        inputN.setOutline(1, sf::Color::Red);

    inputR.setCharacterSize(10);
    inputR.setString(tempR);
    inputR.alignCenter();
    if (isRSelected)
        inputR.setOutline(1, sf::Color::Red);

    inputZ.setCharacterSize(10);
    inputZ.setString(tempZ);
    inputZ.alignCenter();
    if (isZSelected)
        inputZ.setOutline(1, sf::Color::Red);

    inputN.Draw(window);
    inputR.Draw(window);
    inputZ.Draw(window);

    if (!tempN.empty() && !tempR.empty()) {
        if (ex1 == true) {
            double R = std::stoi(tempR), N = std::stoi(tempN);
            double alpha = 0;
            double dalpha = 2 * PI / N;
            Point* points = new Point[N + 1];
            for (int i = 0; i < N + 1; i++) {
                points[i].x = (int)(R * cos(alpha)) + shape.getSize().x / 2;
                points[i].y = (int)(R * sin(alpha)) + shape.getSize().y / 2;
                alpha += dalpha;
            }

            for (int i = 0; i <= N - 1; i++) {
                Line::DrawLine(points[i], points[i + 1], window);
            }
        }
        else if (ex2 == true) {
            double R = std::stod(tempR), N = std::stod(tempN);
            double alpha = 0;
            double dalpha = 360 / N;
            Point* points = new Point[N + 1];
            for (int i = 0; i < N + 1; i++) {
                points[i].x = (int)(R * cos(alpha)) + shape.getSize().x / 2;
                points[i].y = (int)(R * sin(alpha)) + shape.getSize().y / 2;
                alpha += dalpha;
            }

            for (int i = 0; i <= N - 1; i++) {
                Line::DrawLine(points[i], points[i + 1], window);
            }
        }
        else if (ex3 == true && !tempZ.empty()) {
            if (std::stoi(tempN) > 50)
                tempN = "50";
            double R = std::stoi(tempR), N = std::stoi(tempN), Z = std::stoi(tempZ);
            double alpha = 0;
            double dalpha = 2 * PI / N;
            double dR = R / (N * Z);
            R = 0;
            Point* points = new Point[(int)N * (int)Z];
            for (int i = 0; i < N * Z; i++) {
                points[i].x = (int)(R * cos(alpha)) + shape.getSize().x / 2;
                points[i].y = (int)(R * sin(alpha)) + shape.getSize().y / 2;
                alpha += dalpha;
                R += dR;
            }

            for (int i = 0; i <= (N * Z) - 2; i++) {
                Line::DrawLine(points[i], points[i + 1], window);
            }
        }
        else if (ex4 == true) {
            double R = std::stoi(tempR), N = std::stoi(tempN);
            double alpha = 0;
            double dalpha = 2 * PI / N;
            Point* points = new Point[N + 1];
            for (int i = 0; i < N + 1; i++) {
                points[i].x = (int)(R * cos(alpha)) + shape.getSize().x / 2;
                points[i].y = (int)(R * sin(alpha)) + shape.getSize().y / 2;
                alpha += dalpha;
            }
            for (int i = 0; i <= N - 1; i++) {
                for (int j = i; j <= N - 1; j++) {
                    Line::DrawLine(points[i], points[j], window);
                }
            }
        }
        else if (ex5 == true) {
            double  N = std::stoi(tempN), a = 500.0;
            double calpha = 0;
            double alpha = 15;
            for (int i = 0; i < N; i++) {
                sf::RectangleShape square;
                square.setSize(sf::Vector2f(a, a));
                square.rotate(calpha);
                square.setOutlineThickness(1);
                square.setOutlineColor(sf::Color::Red);
                square.setFillColor(sf::Color::Transparent);
                square.setOrigin(square.getSize().x / 2, square.getSize().y / 2);
                square.setPosition(shape.getSize().x / 2, shape.getSize().y / 2);
                window.draw(square);
                a = (sqrt(2.0 / 3.0) * sqrt(pow(a, 2)));
                calpha += +alpha;
            }
        }
    }
    window.display();
}