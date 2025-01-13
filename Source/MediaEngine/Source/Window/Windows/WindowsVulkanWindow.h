#pragma once
#include "MediaEngine/Include/Core/PlatformDetection.h"

#ifdef ME_PLATFORM_WINDOWS

#include "ThirdParty/glfw-3.4/include/GLFW/glfw3.h"
#include "MediaEngine/Include/Window/Window.h"

namespace ME
{
class WindowsVulkanWindow : public Window
{
public:
    virtual bool InitWindow(const WindowProps& props) override;
    virtual void Destroy() override;
    virtual void PollEvents() override;
    virtual uint32_t GetWidth() const override;
    virtual uint32_t GetHeight() const override;
    virtual void SetEventCallback(const EventCallbackFn& callback) override;
    virtual void* GetNativeWindow() const override;

private:
    static void GLFWErrorCallback(int error, const char* description);
    void SetEventCallback();

private:
    struct WindowData
    {
        std::string Title;
        uint32_t Width = 0;
        uint32_t Height = 0;
        bool VSync = false;
        EventCallbackFn EventCallback;
    };

    WindowData m_Data;
    GLFWwindow* m_Window = nullptr;
};
}  //namespace ME

#endif