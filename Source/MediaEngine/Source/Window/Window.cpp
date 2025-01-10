#include "MediaEngine/Include/Window/Window.h"
#include "Windows/WindowsVulkanWindow.h"

namespace ME
{
std::shared_ptr<Window> Window::Create()
{
    auto wnd = std::make_shared<WindowsVulkanWindow>();
    return wnd;
}
}  //namespace ME