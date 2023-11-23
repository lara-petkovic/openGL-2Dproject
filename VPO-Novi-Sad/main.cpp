//Autor: Lara Petkoviæ RA 185/2020
//Opis: Protiv-vazdušna odbrana Novog Sada 

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <glm/glm.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

unsigned int compileShader(GLenum type, const char* source);
unsigned int createShader(const char* vsSource, const char* fsSource);
static unsigned loadImageToTexture(const char* filePath);

int main(void)
{
    srand(static_cast<unsigned>(time(nullptr)));

    if (!glfwInit())
    {
        std::cout<<"Greska prilikom ucitavanja GLFW biblioteke!\n";
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;
    unsigned int wWidth = 900;
    unsigned int wHeight = 900;
    const char wTitle[] = "Protiv-vazdusna odbrana Novog Sada";
    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
    int xPos = (mode->width - wWidth) / 2;
    int yPos = (mode->height - wHeight) / 2;
    window = glfwCreateWindow(wWidth, wHeight, wTitle, NULL, NULL);
    glfwSetWindowPos(window, xPos, yPos);
    
    if (window == NULL)
    {
        std::cout << "Prozor nije napravljen! :(\n";
        glfwTerminate();
        return 2;
    }

    glfwMakeContextCurrent(window);


    if (glewInit() != GLEW_OK)
    {
        std::cout << "Greska prilikom ucitavanja GLEW biblioteke!\n";
        return 3;
    }

    unsigned int unifiedShader = createShader("pvo.vert", "pvo.frag");

    float vertices[] = {
    -1.0, -1.0,  0.0, 0.0,
     1.0, -1.0,  1.0, 0.0,
    -1.0,  1.0,  0.0, 1.0,

     1.0, -1.0,  1.0, 0.0,
     1.0,  1.0,  1.0, 1.0
    };


    unsigned int stride = (2 + 2) * sizeof(float);

    unsigned int VAO;
    

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
   
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    
    //Tekstura
    unsigned mapTexture = loadImageToTexture("res/novi-sad.png");
    glBindTexture(GL_TEXTURE_2D, mapTexture);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
    unsigned uTexLoc = glGetUniformLocation(unifiedShader, "uTex");
    glUniform1i(uTexLoc, 0);
 
    float pointRadii[5] = { 0.015, 0.015, 0.015, 0.015, 0.015 };
    float pointSpeeds[5] = { 0.00005, 0.00006, 0.00007, 0.00008, 0.00009 };
    float pointColorTimers[5] = { 0.0, 0.0, 0.0, 0.0, 0.0 }; // Sve taèke poèinju pulsiranje istovremeno


    glm::vec2 pointPositions[5];
    for (int i = 0; i < 5; ++i) {
        pointPositions[i].x = (rand() % 100) / 100.0;
        pointPositions[i].y = (rand() % 100) / 100.0;
    }


    // Postavljamo uniformne promenljive za pulsirajuæe taèke
    glUniform2fv(glGetUniformLocation(unifiedShader, "pointPositions"), 5, &pointPositions[0].x);
    glUniform1fv(glGetUniformLocation(unifiedShader, "pointRadii"), 5, pointRadii);
    glUniform1fv(glGetUniformLocation(unifiedShader, "pointSpeeds"), 5, pointSpeeds);
    glUniform1fv(glGetUniformLocation(unifiedShader, "pointColorTimers"), 5, pointColorTimers);

    GLuint pointPositionsLocation = glGetUniformLocation(unifiedShader, "pointPositions");
    GLuint pointRadiiLocation = glGetUniformLocation(unifiedShader, "pointRadii");
    GLuint pointSpeedsLocation = glGetUniformLocation(unifiedShader, "pointSpeeds");
    GLuint pointColorTimersLocation = glGetUniformLocation(unifiedShader, "pointColorTimers");


    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }

        glClearColor(0.5, 0.5, 0.5, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(unifiedShader);
        glBindVertexArray(VAO);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mapTexture);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);
        glBindTexture(GL_TEXTURE_2D, 0);

        GLuint circleColorLoc = glGetUniformLocation(unifiedShader, "circleColor");
        glUniform4f(circleColorLoc, 0.0f, 1.0f, 0.0f, 1.0f); // Green color

        glUniform2fv(pointPositionsLocation, 5, &pointPositions[0].x);
        glUniform1fv(pointRadiiLocation, 5, pointRadii);
        glUniform1fv(pointSpeedsLocation, 5, pointSpeeds);
        glUniform1fv(pointColorTimersLocation, 5, pointColorTimers);


        const float deltaTime = 0.016;
        for (int i = 0; i < 5; ++i) {
            pointColorTimers[i] += deltaTime;
        }

        glUniform1fv(pointColorTimersLocation, 5, pointColorTimers);
        // Update helicopter positions to appear from random edges and move towards the city center
        for (int i = 0; i < 5; ++i)
        {
            if (pointPositions[i].x < -1.0 || pointPositions[i].x > 1.0 || pointPositions[i].y < -1.0 || pointPositions[i].y > 1.0)
            {
                // Reset position when the point goes out of the screen
                int edge = rand() % 4;  // Randomly select one of the four edges (0: top, 1: right, 2: bottom, 3: left)

                switch (edge)
                {
                case 0:  // Top edge
                    pointPositions[i].x = (rand() % 100) / 100.0;  // Random x-coordinate
                    pointPositions[i].y = 1.0;  // Top edge
                    break;
                case 1:  // Right edge
                    pointPositions[i].x = 1.0;  // Right edge
                    pointPositions[i].y = (rand() % 100) / 100.0;  // Random y-coordinate
                    break;
                case 2:  // Bottom edge
                    pointPositions[i].x = (rand() % 100) / 100.0;  // Random x-coordinate
                    pointPositions[i].y = -1.0;  // Bottom edge
                    break;
                case 3:  // Left edge
                    pointPositions[i].x = -1.0;  // Left edge
                    pointPositions[i].y = (rand() % 100) / 100.0;  // Random y-coordinate
                    break;
                }
            }
            else
            {
                // Move towards the city center
                glm::vec2 cityCenter(0.71, 0.53);
                glm::vec2 direction = glm::normalize(cityCenter - pointPositions[i]);
                pointPositions[i] += direction * pointSpeeds[i];
            }
        }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glDeleteTextures(1, &mapTexture);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(unifiedShader);

    glfwTerminate();
    return 0;
}

unsigned int compileShader(GLenum type, const char* source)
{
    std::string content = "";
    std::ifstream file(source);
    std::stringstream ss;
    if (file.is_open())
    {
        ss << file.rdbuf();
        file.close();
        std::cout << "Uspesno procitan fajl sa putanje \"" << source << "\"!" << std::endl;
    }
    else {
        ss << "";
        std::cout << "Greska pri citanju fajla sa putanje \"" << source << "\"!" << std::endl;
    }
     std::string temp = ss.str();
     const char* sourceCode = temp.c_str();

    int shader = glCreateShader(type);
    
    int success;
    char infoLog[512];
    glShaderSource(shader, 1, &sourceCode, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        if (type == GL_VERTEX_SHADER)
            printf("VERTEX");
        else if (type == GL_FRAGMENT_SHADER)
            printf("FRAGMENT");
        printf(" sejder ima gresku! Greska: \n");
        printf(infoLog);
    }
    return shader;
}
unsigned int createShader(const char* vsSource, const char* fsSource)
{
    
    unsigned int program;
    unsigned int vertexShader;
    unsigned int fragmentShader;

    program = glCreateProgram();

    vertexShader = compileShader(GL_VERTEX_SHADER, vsSource);
    fragmentShader = compileShader(GL_FRAGMENT_SHADER, fsSource);

    
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);
    glValidateProgram(program);

    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
    if (success == GL_FALSE)
    {
        glGetShaderInfoLog(program, 512, NULL, infoLog);
        std::cout << "Objedinjeni sejder ima gresku! Greska: \n";
        std::cout << infoLog << std::endl;
    }

    glDetachShader(program, vertexShader);
    glDeleteShader(vertexShader);
    glDetachShader(program, fragmentShader);
    glDeleteShader(fragmentShader);

    return program;
}
static unsigned loadImageToTexture(const char* filePath) {
    int TextureWidth;
    int TextureHeight;
    int TextureChannels;
    unsigned char* ImageData = stbi_load(filePath, &TextureWidth, &TextureHeight, &TextureChannels, 0);
    if (ImageData != NULL)
    {
        stbi__vertical_flip(ImageData, TextureWidth, TextureHeight, TextureChannels);

        GLint InternalFormat = -1;
        switch (TextureChannels) {
        case 1: InternalFormat = GL_RED; break;
        case 3: InternalFormat = GL_RGB; break;
        case 4: InternalFormat = GL_RGBA; break;
        default: InternalFormat = GL_RGB; break;
        }

        unsigned int Texture;
        glGenTextures(1, &Texture);
        glBindTexture(GL_TEXTURE_2D, Texture);
        glTexImage2D(GL_TEXTURE_2D, 0, InternalFormat, TextureWidth, TextureHeight, 0, InternalFormat, GL_UNSIGNED_BYTE, ImageData);
        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(ImageData);
        return Texture;
    }
    else
    {
        std::cout << "Textura nije ucitana! Putanja texture: " << filePath << std::endl;
        stbi_image_free(ImageData);
        return 0;
    }
}