#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <math.h>

#include "Shader.h"
#include "Line.h"
#include "Camera.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "objects/triangles.h"


#define ENABLE_FULLSCREEN 0
#define RESIZABLE 0
#define VSYNC 0

GLFWwindow* window;
GLFWmonitor* monitor;
unsigned int WIDTH = 1000;
unsigned int HEIGHT = 1000;

// Timing
float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f;
bool polling_points = false;
Camera camera;

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}


std::vector<glm::vec3> points_buffer;
std::vector<float> points;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void renderLines();

int main() {

    // Greet on the terminal
    std::cout << "Hello, RTSkippy!" << std::endl;

    glfwSetErrorCallback(error_callback);

    // Init GLFW
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Setup GLFW
    glfwWindowHint(GLFW_RESIZABLE, RESIZABLE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Setup Monitor to Primary
    monitor = glfwGetPrimaryMonitor();

    // Handle case where we want to render at the maximum monitor resolution aka Fullscreen :-)
    if (ENABLE_FULLSCREEN) {
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        WIDTH = mode->width;
        HEIGHT = mode->height;
    }
    std::cout <<  "Using Window Size : " <<  WIDTH << " x " << HEIGHT << std::endl;

    // Create GLFW Window
    window = glfwCreateWindow(WIDTH, HEIGHT, "RTSkippy", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to open window GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Init GLEW
    glewExperimental = true;
    GLenum err = glewInit();
    if(err != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Display used OpenGL Version
    std::cout << glGetString(GL_VERSION) << std::endl;

    camera.position = vec3(3,3,3);

    // 3d lines example
    Line line1(vec3(0,0,0), vec3(1,0,0));
    line1.setColor(vec3(1,0,0));
    Line line2(vec3(0,0,0), vec3(0,1,0));
    line2.setColor(vec3(0,1,0));
    Line line3(vec3(0,0,0), vec3(0,0,1));
    line3.setColor(vec3(0,0,1));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) WIDTH / (float)HEIGHT, 0.1f, 100.0f);

    float angle = 0.0f;
    float rotationSpeed = 25.0f;

    // 2d line example
    vec3 start = vec3(WIDTH/2,HEIGHT/2,0);
    vec3 end = vec3(WIDTH,HEIGHT,0);

    float x1 = start.x;
    float y1 = start.y;
    float x2 = end.x;
    float y2 = end.y;
    float w = WIDTH;
    float h = HEIGHT;

    // convert 3d world space position 2d screen space position
    x1 = 2*x1 / w - 1;
    y1 = 2*y1 / h - 1;

    x2 = 2*x2 / w - 1;
    y2 = 2*y2 / h - 1;

    start.x = x1;
    start.y = y1;
    end.x = x2;
    end.y = y2;


    // Enable or Disable VSYNC
    glfwSwapInterval(VSYNC);


    while(!glfwWindowShouldClose(window)) {

        // Get time
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        // std::cout << "t : " << currentFrame << std::endl;

        // Process Input
        processInput(window);

        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        angle = deltaTime * rotationSpeed;

        // update camera position (rotating)
        camera.position = vec3(3 * cos(glm::radians(angle)), 3, 3 * sin(glm::radians(angle)));
        glm::mat4 view = glm::lookAt(camera.position, vec3(0, 0, 0), glm::vec3(0, 1, 0));


        line1.setMVP(projection * view);
        line2.setMVP(projection * view);
        line3.setMVP(projection * view);

        line1.draw();
        line2.draw();
        line3.draw();

        MLine mline(points);
        mline.setup();
        mline.draw();

        if (polling_points)
            renderLines();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void renderLines()
{
    double xPos, yPos;
    //Getting cursor position
    glfwGetCursorPos(window, &xPos, &yPos);
    glm::vec3 p(0.f,0.f,0.f);
    p.x = xPos;
    p.y = HEIGHT - yPos;
    p.z = 0;
    // std::cout << "(" << p.x << "," << p.y << ")" << std::endl;


    if (points_buffer.empty()) {
        points_buffer.push_back(p);
    }
    else if (points_buffer.back().x != p.x and points_buffer.back().y != p.y) {
        points_buffer.push_back(p);
        if (points_buffer.size() > 2)
        {
            auto start = points_buffer.at(points_buffer.size() - 2);
            auto end = points_buffer.back();
            float x1 = start.x;
            float y1 = start.y;
            float x2 = end.x;
            float y2 = end.y;
            float w = WIDTH;
            float h = HEIGHT;

            // convert 3d world space position 2d screen space position
            x1 = 2*x1 / w - 1;
            y1 = 2*y1 / h - 1;

            x2 = 2*x2 / w - 1;
            y2 = 2*y2 / h - 1;

            start.x = x1;
            start.y = y1;
            end.x = x2;
            end.y = y2;

            points.push_back(start.x);
            points.push_back(start.y);
            points.push_back(start.z);
            points.push_back(end.x);
            points.push_back(end.y);
            points.push_back(end.z);
        }
    }

    std::cout << "Total Points : " << points_buffer.size() << std::endl;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS and glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        points_buffer.clear();
        points.clear();
    }

    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS and glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        polling_points = true;
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS and glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        polling_points = false;
    }
}
