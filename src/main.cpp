#include <iostream>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>

#include "vulkan/Context.hpp"

void error_callback(int error, const char *description)
{
    std::cerr << "Error" << error << ": " << description << "\n"
              << std::endl;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    (void)scancode;
    (void)mods;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return 1;
    }

    glfwSetErrorCallback(error_callback);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    GLFWwindow *window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to initialize GLFW Window" << std::endl;
        return 1;
    }
    glfwSetKeyCallback(window, key_callback);

    Acamarachi::Vulkan::Context context = Acamarachi::Vulkan::Context();
    context.initialize("Test", reinterpret_cast<Acamarachi::Vulkan::GetRequiredExtensions*>(glfwGetRequiredInstanceExtensions), window, reinterpret_cast<Acamarachi::Vulkan::CreateWindowSurfaceFunction*>(glfwCreateWindowSurface));


    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        context.frameInfo.draw(context.device, context.swapchain);
    }

    context.deinitialize();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}