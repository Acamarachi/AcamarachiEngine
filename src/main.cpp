#include <iostream>
#include <GLFW/glfw3.h>
#include "maths/linear.hpp"

using namespace Acamarachi::Maths;

void error_callback(int error, const char* description)
{
    std::cerr << "Error" << error << ": " << description << "\n" << std::endl;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    (void)scancode;
    (void)mods;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main()
{
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return 1;
    }

    //test
    vec2 a(1.0f);
    vec2 b(2.0f);

    vec2 c = a - a;
    std::cout << c[0] << " " << c[1] << std::endl;
    std::cout << a[0] << " " << a[1] << std::endl;
    std::cout << c[0] << " " << c[1] << std::endl;
    c = c * (a + a)*5.0;

    std::cout << c[0] << " " << c[1] << std::endl;

    glfwSetErrorCallback(error_callback);

    GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to initialize GLFW Window" << std::endl;
        return 1;
    }
    glfwSetKeyCallback(window, key_callback);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }


    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}