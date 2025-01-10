#include "WindowsVulkanWindow.h"
#include "../WindowLog.h"

namespace ME
{
bool WindowsVulkanWindow::InitWindow(const WindowProps& props)
{
    m_Data.Title = props.Title;
    m_Data.Width = props.Width;
    m_Data.Height = props.Height;
    WND_LOG_INFO("Create window {} {} {}", props.Title, props.Width, props.Height);

    glfwSetErrorCallback(GLFWErrorCallback);
    int ret = glfwInit();
    if (ret != GLFW_TRUE)
    {
        WND_LOG_ERROR("glfwInit fail");
        return false;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    m_Window = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), nullptr, nullptr);
    if (m_Window == nullptr)
    {
        WND_LOG_ERROR("glfwCreateWindow fail");
        return false;
    }

    ret = glfwVulkanSupported();
    if (ret != GLFW_TRUE)
    {
        WND_LOG_ERROR("glfwVulkanSupported fail");
        return false;
    }

    return true;
}

void WindowsVulkanWindow::Destroy()
{
    glfwDestroyWindow(m_Window);
    m_Window = nullptr;
    glfwTerminate();
}

void WindowsVulkanWindow::PollEvents()
{
    glfwPollEvents();
}

uint32_t WindowsVulkanWindow::GetWidth() const
{
    return m_Data.Width;
}

uint32_t WindowsVulkanWindow::GetHeight() const
{
    return m_Data.Height;
}

void WindowsVulkanWindow::SetEventCallback(const EventCallbackFn& callback)
{
    m_Data.EventCallback = callback;
}

void* WindowsVulkanWindow::GetNativeWindow() const
{
    return m_Window;
}

void WindowsVulkanWindow::GLFWErrorCallback(int error, const char* description)
{
    WND_LOG_ERROR("GLFW Error ({}): {}", error, description);
}

}  //namespace ME