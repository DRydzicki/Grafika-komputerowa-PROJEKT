// Nag��wki
#include"Engine/EngineLoader.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Kody shader�w
const GLchar* vertexSource = R"glsl(
#version 150 core
in vec3 position;
in vec3 color;
out vec3 Color;
in vec2 aTexCoord;
out vec2 TexCoord;
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 proj;

void main(){
TexCoord = aTexCoord;
Color = color;
gl_Position =  proj * view * model * vec4(position, 1.0);
}
)glsl";

const GLchar* fragmentSource = R"glsl(
#version 150 core
in vec3 Color;
out vec4 outColor;
in vec2 TexCoord;
uniform sampler2D texture1;
uniform sampler2D texture2; 
void main()
{
outColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.5);
//outColor = texture(texture1, TexCoord);
}
)glsl";

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
sf::Vector2i lastMouse;
double yaw = -90; 
double pitch = 0;

float rotate = 0;

void cube(int buffer) {
    const int points = 36;

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f ,0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f ,0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f ,0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f ,0.0f,
    };

    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * points * 8, vertices, GL_STATIC_DRAW);
}


void setView(GLint uniView, float time) {
    float camSpeed = 0.000002f*time;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        cameraPos += camSpeed * cameraFront;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        cameraPos -= camSpeed * cameraFront;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * camSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * camSpeed;
    }

    glm::mat4 view;
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
}

void setViewMouse(GLint uniView, float time, const sf::Window& window) {
    sf::Vector2i locPos = sf::Mouse::getPosition(window);
    sf::Vector2i pos;
    bool relocation = false;
    if (locPos.x <= 0) {
        pos.x = window.getSize().x - 1;
        pos.y = locPos.y;
        relocation = true;
    }
    if (locPos.x >= window.getSize().x - 1) {
        pos.x = 0;
        pos.y = locPos.y;
        relocation = true;
    }
    if (locPos.y <= 0) {
        pos.x = locPos.x;
        pos.y = window.getSize().y-1;
        relocation = true;
    }
    if (locPos.y >= window.getSize().y-1) {
        pos.x = locPos.x;
        pos.y = 0;
        relocation = true;
    }
    if (relocation) {
        sf::Mouse::setPosition(pos, window);
        firstMouse = true;
    }
    locPos = sf::Mouse::getPosition(window);
    if (firstMouse) {
        lastMouse.x = locPos.x;
        lastMouse.y = locPos.y;
        firstMouse = false;
    }

    double xoffset = locPos.x - lastMouse.x;
    double yoffset = locPos.y - lastMouse.y;
    lastMouse.x = locPos.x;
    lastMouse.y = locPos.y;

    double sensitive = 0.8f;
    double camSpeed = 0.00005f * time;

    xoffset *= sensitive;
    yoffset *= sensitive;

    yaw += xoffset * camSpeed;
    pitch -= yoffset * camSpeed;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);

    glm::mat4 view;
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
}

int main()
{
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;

    // Okno renderingu
    sf::Window window(sf::VideoMode(800, 800, 32), "OpenGL", sf::Style::Titlebar | sf::Style::Close, settings);

    // Inicjalizacja GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    // Utworzenie VAO (Vertex Array Object)
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Utworzenie VBO (Vertex Buffer Object) i skopiowanie do niego danych wierzcho�kowych
    GLuint vbo;
    glGenBuffers(1, &vbo);

    int points = 4;
    cube(vbo);

    // Utworzenie i skompilowanie shadera wierzcho�k�w
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    GLint status;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);

    if (!status) {
        std::cout << "Error\n";
        GLchar buffer[1024];
        glGetShaderInfoLog(vertexShader, 1024, NULL, buffer);
        std::cout << buffer << std::endl;
        return 1;
    }

    // Utworzenie i skompilowanie shadera fragment�w
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);

    if (!status) {
        std::cout << "FragmentShader ERROR\n";
        GLchar buffer[1024];

        glGetShaderInfoLog(fragmentShader, 1024, NULL, buffer);
        std::cout << buffer;
        return 1;
    }

    // Zlinkowanie obu shader�w w jeden wsp�lny program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    //glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // Specifikacja formatu danych wierzcho�kowych
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0); //
    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

    GLint TexCoord = glGetAttribLocation(shaderProgram, "aTexCoord");
    glEnableVertexAttribArray(TexCoord);
    glVertexAttribPointer(TexCoord, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));


    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(20.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    GLint uniTrans = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(model));

    GLint uniView = glGetUniformLocation(shaderProgram, "view");

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 800.0f, 0.06f, 100.0f);
    GLint uniProj = glGetUniformLocation(shaderProgram, "proj");

    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

    //Jak do wszyskich obiekt�w w OpenGL do tekstury mo�na odwo�ac si� poprzez identyfikator ID// texture 1
    unsigned int texture1;
    // Generuje tekstury 
    glGenTextures(1, &texture1);  
    //Ustawienie tekstury jako bie��cej (powi�zanie)                                     
    glBindTexture(GL_TEXTURE_2D, texture1);          
    // set the texture wrapping parameters, set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char* data = stbi_load("Resources\\Textures\\metal.bmp", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    //Jak do wszyskich obiekt�w w OpenGL do tekstury mo�na odwo�ac si� poprzez identyfikator ID// texture 1
    unsigned int texture2;
    //Generuje tekstury
    glGenTextures(1, &texture2);
    //Ustawienie tekstury jako bie��cej (powi�zanie)
    glBindTexture(GL_TEXTURE_2D, texture2);
    //set the texture wrapping parameters, set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //load image, create texture and generate mipmaps
    //int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    data = stbi_load("Resources\\Textures\\wood.bmp", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
    glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);


    // Rozpocz�cie p�tli zdarze�
    GLint primitive = GL_TRIANGLE_FAN;
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    window.setMouseCursorGrabbed(true);
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(60);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    sf::Clock clock;
    sf::Time time;
    int c = 0;

    glEnable(GL_DEPTH_TEST);
    while (window.isOpen()) {
        time = clock.restart();
        float fps = 1000000 / time.asMicroseconds();
        c++;
        if (c > fps) {
            window.setTitle(std::to_string(fps));
            c = 0;
        }
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1) {
                primitive = GL_POINTS;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2) {
                primitive = GL_LINES;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num3) {
                primitive = GL_LINE_LOOP;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num4) {
                primitive = GL_LINE_STRIP;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num5) {
                primitive = GL_TRIANGLES;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num6) {
                primitive = GL_TRIANGLE_STRIP;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num7) {
                primitive = GL_TRIANGLE_FAN;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num8) {
                primitive = GL_QUADS;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num9) {
                primitive = GL_QUAD_STRIP;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num0) {
                primitive = GL_POLYGON;
            }

            if (event.type == sf::Event::MouseMoved) {
                setViewMouse(uniView, time.asMicroseconds(), window);
            }

        }
        setView(uniView, time.asMicroseconds());
        // Nadanie scenie koloru czarnego
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Narysowanie tr�jk�ta na podstawie 3 wierzcho�k�w
        //glDrawArrays(primitive, 0, 36);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        glDrawArrays(GL_TRIANGLES, 0, 24);
        // Wymiana bufor�w tylni/przedni
        window.display();
    }
    // Kasowanie programu i czyszczenie bufor�w
    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    // Zamkni�cie okna renderingu
    window.close();
    return 0;
}