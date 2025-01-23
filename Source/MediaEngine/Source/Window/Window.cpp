#include "MediaEngine/Include/Window/Window.h"
#include "MediaEngine/Include/Core/PlatformDetection.h"
#include "Windows/WindowsVulkanWindow.h"
#include "Apple/AppleVulkanWindow.h"

namespace ME
{
Ref<Window> Window::Create()
{
#ifdef ME_PLATFORM_WINDOWS
    auto wnd = CreateRef<WindowsVulkanWindow>();
    return wnd;
#elif defined(ME_PLATFORM_MACOS)
    auto wnd = std::make_shared<AppleVulkanWindow>();
    return wnd;
#else
#error "Not supported platform"
#endif
}
}  //namespace ME
