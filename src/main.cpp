#pragma once
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

    glfwSetErrorCallback(error_callback);

    mat4 m(vec4(1, 9, 3, 4), vec4(1,2,3,4), vec4(3,5,5,4), vec4(4,2,1,3));

    std::cout << determinant(m) << std::endl;

    vec2 a = vec2(4.0f);
    std::cout << a[0] << " " << a[1] << std::endl;
    a = a + vec2(4.0f);
    std::cout << a[0] << " " << a[1] << std::endl;
    a = vec2(2.0f, 6.0f);
    mat2 m2 = { {1.0,2.0},{3.0,1.0} };
    mat2 b2 = { {2.0,1.0},{6.0,1.0} };

    std::cout << a[0] << " " << a[1] << std::endl;
    a = m2 * a;
    std::cout << a[0] << " " << a[1] << std::endl;
    m2 = inverse(m2);

    std::cout << std::endl;
    std::cout << m2[0][0] << " " << m2[0][1] << std::endl;
    std::cout << m2[1][0] << " " << m2[1][1] << std::endl;

    mat3 m3 = { {1,2,3},{3,2,1},{3,1,1} };

    m3 = inverse(m3);

    std::cout << std::endl;
    std::cout << m3[0][0] << " " << m3[0][1] << " " << m3[0][2] << std::endl;
    std::cout << m3[1][0] << " " << m3[1][1] << " " << m3[1][2] << std::endl;
    std::cout << m3[2][0] << " " << m3[2][1] << " " << m3[2][2] << std::endl;


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