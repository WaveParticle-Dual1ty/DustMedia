#include "MediaEngine/Include/Render/RHI.h"
#include <vector>
#include <cstdint>
#include "MediaEngine/Include/Core/PlatformDetection.h"

#ifdef ME_PLATFORM_WINDOWS
#define VK_USE_PLATFORM_WIN32_KHR
#else
#error "Unsupport Plarform"
#endif  // PLATFORM_WINDOWS
#include "vulkan/vulkan.h"

#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include "ThirdParty/glfw-3.4/include/GLFW/glfw3.h"

#include "MediaEngine/Include/Core/Ptr.h"
#include "VulkanRHIResources.h"

namespace ME
{
class VulkanRHI : public RHI
{
public:
    virtual bool Initialize(std::shared_ptr<Window> wnd) override;
    virtual bool Resize(uint32_t width, uint32_t height) override;
    virtual bool PrepareForNextFrame() override;
    virtual bool SubmmitRenderCommands() override;
    virtual bool Present() override;

    virtual Ref<RHICommandBuffer> GetCurrentCommandBuffer() const override;

    virtual Ref<RHITexture2D> CreateTexture2D(RHITexture2DCreateDesc desc) override;

    virtual bool BeginCommandBuffer(Ref<RHICommandBuffer> commandBuffer) override;
    virtual bool EndCommandBuffer(Ref<RHICommandBuffer> commandBuffer) override;

    // test interface
    virtual bool ClearBackBuffer(Ref<RHICommandBuffer> commandBuffer, float r, float g, float b, float a) override;

private:
    struct VulkanQueue
    {
        VkQueue Queue = VK_NULL_HANDLE;
        uint32_t QueueFamilyIndex = UINT32_MAX;
    };

private:
    bool IsExtensionAvailable(const std::vector<VkExtensionProperties>& properties, const char* extension);
    VkInstance CreateInstance();
    VkSurfaceKHR CreateSurface(VkInstance instance, GLFWwindow* wnd);
    VkPhysicalDevice SetupPhysicalDevice(VkInstance instance);
    bool SetupQueueFamilyIndices(
        VkPhysicalDevice physicalDevice,
        VkSurfaceKHR surface,
        uint32_t& queueFamilyIndexForGraphic,
        uint32_t& queueFamilyIndexForPresent,
        uint32_t& queueFamilyIndexForCompute);
    VkDevice CreateDevice(
        VkPhysicalDevice physicalDevice,
        uint32_t queueFamilyIndexForGraphic,
        uint32_t queueFamilyIndexForPresent,
        uint32_t queueFamilyIndexForCompute);
    bool GetQueues(
        VkDevice device,
        uint32_t queueFamilyIndexForGraphic,
        uint32_t queueFamilyIndexForPresent,
        uint32_t queueFamilyIndexForCompute,
        VulkanQueue& graphicQueue,
        VulkanQueue& presentQueue,
        VulkanQueue& computeQueue);
    bool CreateCommandResourcesForGraphic(
        VkCommandPool& commandPool,
        VkCommandBuffer& commandBuffer,
        VkFence& fenceForBuffer,
        VkDevice device,
        VulkanQueue graphicQueue);
    std::vector<VkSurfaceFormatKHR> GetSupportSurfaceFormats(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
    std::vector<VkPresentModeKHR> GetSupportPresentModes(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
    bool CreateSwapchainResources(
        VkSwapchainKHR& swapchain,
        std::vector<VkImage>& swapchainImages,
        std::vector<VkSemaphore>& imageAcquiredSemaphores,
        std::vector<VkSemaphore>& renderCompleteSemaphores,
        VkPhysicalDevice physicalDevie,
        VkDevice device,
        VulkanQueue graphicQueue,
        VulkanQueue presentQueue,
        VkSurfaceKHR surface,
        VkExtent2D extend,
        uint32_t minImageCount);

private:
    VkInstance m_Instance = VK_NULL_HANDLE;
    VkSurfaceKHR m_Surface = VK_NULL_HANDLE;
    VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
    VkDevice m_Device = VK_NULL_HANDLE;
    VulkanQueue m_GraphicQueue;
    VulkanQueue m_PresentQueue;
    VulkanQueue m_ComputeQueue;
    VkCommandPool m_CommandPool = VK_NULL_HANDLE;
    Ref<VulkanRHICommandBuffer> m_RHICommandBuffer;
    VkFence m_FenceForCommandBuffer = VK_NULL_HANDLE;
    VkSwapchainKHR m_Swapchain = VK_NULL_HANDLE;
    std::vector<VkImage> m_SwapchainImages;
    uint32_t m_SwapchainFrameIndex = 0;
    std::vector<VkSemaphore> m_ImageAcquiredSemaphores;
    std::vector<VkSemaphore> m_RenderCompleteSemaphores;
    uint32_t m_GraphicSemaphoreCnt = 0;
    uint32_t m_GraphicSemaphoreIndex = 0;
};

}  //namespace ME