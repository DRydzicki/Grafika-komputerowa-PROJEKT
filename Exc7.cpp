//// Nag³ówki
//#include"Engine/EngineLoader.h"
//#include <GL/glew.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//thread_local std::mt19937 gen{ std::random_device{}() };
//template<typename T>
//T random(T min, T max) {
//    return std::uniform_int_distribution<T>{min, max}(gen);
//}
//
//
//// Kody shaderów
//const GLchar* vertexSource = R"glsl(
//#version 150 core
//in vec3 position;
//in vec3 color;
//    uniform mat4 model;
//    uniform mat4 view;
//    uniform mat4 proj;
//out vec3 Color;
//void main(){
//Color = color;
//gl_Position =  proj * view * model * vec4(position, 1.0);
//}
//)glsl";
//
//const GLchar* fragmentSource = R"glsl(
//#version 150 core
//in vec3 Color;
//out vec4 outColor;
//void main()
//{
//outColor = vec4(Color, 1.0);
//}
//)glsl";
//
//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
//glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
//
//
//float rotate = 0;
//
//void cube(int buffer) {
//    const int points = 36;
//
//    float vertices[] = {
//        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
//        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
//        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
//        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
//
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
//        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
//        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
//        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
//
//        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
//        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
//        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
//
//        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
//        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
//        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
//        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
//        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
//        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
//
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
//        0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
//        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
//        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
//
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
//        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
//        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
//        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f
//    };
//
//    glBindBuffer(GL_ARRAY_BUFFER, buffer);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * points * 6, vertices, GL_STATIC_DRAW);
//}
//
//
//void setView(GLint uniView) {
//    float camSpeed = 0.005f;
//
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
//        cameraPos += camSpeed * cameraFront;
//    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
//        cameraPos -= camSpeed * cameraFront;
//    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
//        rotate -= camSpeed;
//        cameraFront.x = sin(rotate);
//        cameraFront.z = -cos(rotate);
//    }
//    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
//        rotate += camSpeed;
//        cameraFront.x = sin(rotate);
//        cameraFront.z = -cos(rotate);
//    }
//
//    glm::mat4 view;
//    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
//    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
//}
//
//int main()
//{
//    sf::ContextSettings settings;
//    settings.depthBits = 24;
//    settings.stencilBits = 8;
//
//    // Okno renderingu
//    sf::Window window(sf::VideoMode(800, 800, 32), "OpenGL", sf::Style::Titlebar | sf::Style::Close, settings);
//
//
//
//    // Inicjalizacja GLEW
//    glewExperimental = GL_TRUE;
//    glewInit();
//
//    // Utworzenie VAO (Vertex Array Object)
//    GLuint vao;
//    glGenVertexArrays(1, &vao);
//    glBindVertexArray(vao);
//
//    // Utworzenie VBO (Vertex Buffer Object)
//    // i skopiowanie do niego danych wierzcho³kowych
//    GLuint vbo;
//    glGenBuffers(1, &vbo);
//
//
//
//    int points = 4;
//    //object(points, vbo);
//    cube(vbo);
//
//    // Utworzenie i skompilowanie shadera wierzcho³ków
//    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertexShader, 1, &vertexSource, NULL);
//    glCompileShader(vertexShader);
//
//    GLint status;
//    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
//
//    if (!status) {
//        std::cout << "Error\n";
//        GLchar buffer[1024];
//        glGetShaderInfoLog(vertexShader, 1024, NULL, buffer);
//        std::cout << buffer << std::endl;
//        return 1;
//    }
//
//    // Utworzenie i skompilowanie shadera fragmentów
//    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
//    glCompileShader(fragmentShader);
//
//    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
//
//    if (!status) {
//        std::cout << "FragmentShader ERROR\n";
//        GLchar buffer[1024];
//
//        glGetShaderInfoLog(fragmentShader, 1024, NULL, buffer);
//        std::cout << buffer;
//        return 1;
//    }
//
//
//    // Zlinkowanie obu shaderów w jeden wspólny program
//    GLuint shaderProgram = glCreateProgram();
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    //glBindFragDataLocation(shaderProgram, 0, "outColor");
//    glLinkProgram(shaderProgram);
//    glUseProgram(shaderProgram);
//
//    // Specifikacja formatu danych wierzcho³kowych
//    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
//    glEnableVertexAttribArray(posAttrib);
//    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0); //
//    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
//    glEnableVertexAttribArray(colAttrib);
//    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
//
//
//    glm::mat4 model = glm::mat4(1.0f);
//    model = glm::rotate(model, glm::radians(20.0f), glm::vec3(0.0f, 0.0f, 1.0f));
//
//    GLint uniTrans = glGetUniformLocation(shaderProgram, "model");
//    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(model));
//
//    GLint uniView = glGetUniformLocation(shaderProgram, "view");
//
//    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 800.0f, 0.06f, 100.0f);
//    GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
//
//    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));
//
//    // Rozpoczêcie pêtli zdarzeñ
//
//    sf::Clock clock;
//    double t = 0.0;
//    double dt = 1 / 120;
//    GLint primitive = GL_TRIANGLE_FAN;
//    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
//   
//
//    glEnable(GL_DEPTH_TEST);
//    while (window.isOpen()) {
//        double time = clock.getElapsedTime().asMicroseconds();
//        clock.restart();
//        t += time;
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
//                window.close();
//            }
//            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1) {
//                primitive = GL_POINTS;
//            }
//            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2) {
//                primitive = GL_LINES;
//            }
//            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num3) {
//                primitive = GL_LINE_LOOP;
//            }
//            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num4) {
//                primitive = GL_LINE_STRIP;
//            }
//            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num5) {
//                primitive = GL_TRIANGLES;
//            }
//            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num6) {
//                primitive = GL_TRIANGLE_STRIP;
//            }
//            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num7) {
//                primitive = GL_TRIANGLE_FAN;
//            }
//            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num8) {
//                primitive = GL_QUADS;
//            }
//            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num9) {
//                primitive = GL_QUAD_STRIP;
//            }
//            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num0) {
//                primitive = GL_POLYGON;
//            }
//        }
//
//        setView(uniView);
//        // Nadanie scenie koloru czarnego
//        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        // Narysowanie trójk¹ta na podstawie 3 wierzcho³ków
//        glDrawArrays(primitive, 0, 36);
//        // Wymiana buforów tylni/przedni
//        window.display();
//    }
//    // Kasowanie programu i czyszczenie buforów
//    glDeleteProgram(shaderProgram);
//    glDeleteShader(fragmentShader);
//    glDeleteShader(vertexShader);
//    glDeleteBuffers(1, &vbo);
//    glDeleteVertexArrays(1, &vao);
//    // Zamkniêcie okna renderingu
//    window.close();
//    return 0;
//}