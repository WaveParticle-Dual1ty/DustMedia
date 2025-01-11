#include "AppleVulkanWindow.h"

#ifdef ME_PLATFORM_MACOS

#include "MediaEngine/Include/Event/KeyCodes.h"
#include "MediaEngine/Include/Event/MouseCodes.h"
#include "MediaEngine/Include/Event/ApplicationEvent.h"
#include "MediaEngine/Include/Event/KeyEvent.h"
#include "MediaEngine/Include/Event/MouseEvent.h"
#include "../WindowLog.h"
#include "../GlfwUtils.h"

namespace ME
{
bool AppleVulkanWindow::InitWindow(const WindowProps& props)
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

    int major = 0;
    int minior = 0;
    int rev = 0;
    glfwGetVersion(&major, &minior, &rev);
    WND_LOG_INFO("Glfw vertsion: {}.{}.{}", major, minior, rev);

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    m_Window = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), nullptr, nullptr);
    if (m_Window == nullptr)
    {
        WND_LOG_ERROR("glfwCreateWindow fail");
        return false;
    }

#if 0
    ret = glfwVulkanSupported();
    if (ret != GLFW_TRUE)
    {
        WND_LOG_ERROR("glfwVulkanSupported fail");
        return false;
    }
#endif

    SetEventCallback();
    return true;
}

void AppleVulkanWindow::Destroy()
{
    glfwDestroyWindow(m_Window);
    m_Window = nullptr;
    glfwTerminate();
}

void AppleVulkanWindow::PollEvents()
{
    glfwPollEvents();
}

uint32_t AppleVulkanWindow::GetWidth() const
{
    return m_Data.Width;
}

uint32_t AppleVulkanWindow::GetHeight() const
{
    return m_Data.Height;
}

void AppleVulkanWindow::SetEventCallback(const EventCallbackFn& callback)
{
    m_Data.EventCallback = callback;
}

void* AppleVulkanWindow::GetNativeWindow() const
{
    return m_Window;
}

void AppleVulkanWindow::GLFWErrorCallback(int error, const char* description)
{
    WND_LOG_ERROR("GLFW Error ({}): {}", error, description);
}

void AppleVulkanWindow::SetEventCallback()
{
    glfwSetWindowUserPointer(m_Window, &m_Data);

    glfwSetWindowSizeCallback(
        m_Window,
        [](GLFWwindow* window, int width, int height)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;
            WindowResizeEvent event(width, height);
            data.EventCallback(event);
        });

    glfwSetWindowCloseCallback(
        m_Window,
        [](GLFWwindow* window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallback(event);
        });

    glfwSetKeyCallback(
        m_Window,
        [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyCode code = Utils::ConvertGLFWKeycodeToHazelKeycode(key);
                    KeyPressedEvent event(code, false);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyCode code = Utils::ConvertGLFWKeycodeToHazelKeycode(key);
                    KeyReleasedEvent event(code);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyCode code = Utils::ConvertGLFWKeycodeToHazelKeycode(key);
                    KeyPressedEvent event(code, true);
                    data.EventCallback(event);
                    break;
                }
            }
        });

    glfwSetCharCallback(
        m_Window,
        [](GLFWwindow* window, unsigned int keycode)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            KeyTypedEvent event(keycode);
            data.EventCallback(event);
        });

    glfwSetMouseButtonCallback(
        m_Window,
        [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseCode code = Utils::ConvertGLFWMouseButtonToHazelMouseCode(button);
                    MouseButtonPressedEvent event(code);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseCode code = Utils::ConvertGLFWMouseButtonToHazelMouseCode(button);
                    MouseButtonReleasedEvent event(code);
                    data.EventCallback(event);
                    break;
                }
            }
        });

    glfwSetScrollCallback(
        m_Window,
        [](GLFWwindow* window, double xOffset, double yOffset)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.EventCallback(event);
        });

    glfwSetCursorPosCallback(
        m_Window,
        [](GLFWwindow* window, double xPos, double yPos)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseMovedEvent event((float)xPos, (float)yPos);
            data.EventCallback(event);
        });

    glfwSetDropCallback(
        m_Window,
        [](GLFWwindow* window, int count, const char** paths)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            std::vector<std::string> dropFiles;
            if (count >= 1)
            {
                dropFiles.reserve(count);
                for (int i = 0; i < count; ++i)
                {
                    dropFiles.emplace_back(paths[i]);
                }
            }

            FileDropEvent event(dropFiles);
            data.EventCallback(event);
        });
}

}  //namespace ME

#endif
