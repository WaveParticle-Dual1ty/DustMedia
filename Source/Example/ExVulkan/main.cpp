#include <iostream>
#include "vulkan/vulkan.h"

int main(int argc, char** argv)
{
    static_cast<void>(argc);
    static_cast<void>(argv);

    uint32_t vkAPIVersion = 0;
    VkResult res = vkEnumerateInstanceVersion(&vkAPIVersion);
    if (res != VK_SUCCESS)
    {
        std::cout << "vkEnumerateInstanceVersion fail" << std::endl;
        return -1;
    }

    uint32_t majorVersion = VK_VERSION_MAJOR(vkAPIVersion);
    uint32_t minorVersion = VK_VERSION_MINOR(vkAPIVersion);
    uint32_t patchVersion = VK_VERSION_PATCH(vkAPIVersion);
    printf("System vulkan version: %d.%d.%d\n", majorVersion, minorVersion, patchVersion);

    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pNext = nullptr;
    appInfo.pApplicationName = "Application";
    appInfo.applicationVersion = 1;
    appInfo.pEngineName = "Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_MAKE_VERSION(1, 1, 0);

    VkInstanceCreateInfo instanceCreateInfo = {};
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pNext = nullptr;
    instanceCreateInfo.flags = 0;
    instanceCreateInfo.pApplicationInfo = &appInfo;
    instanceCreateInfo.enabledLayerCount = 0;
    instanceCreateInfo.ppEnabledLayerNames = nullptr;
    instanceCreateInfo.enabledExtensionCount = 0;
    instanceCreateInfo.ppEnabledExtensionNames = nullptr;

    VkInstance instance = VK_NULL_HANDLE;
    res = vkCreateInstance(&instanceCreateInfo, nullptr, &instance);
    if (res != VK_SUCCESS)
    {
        std::cout << "vkCreateInstance fail" << std::endl;
        return -1;
    }

    std::cout << "End" << std::endl;
    return 1;
}
