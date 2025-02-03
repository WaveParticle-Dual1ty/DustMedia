#include "MediaEngine/Include/Render/RHI.h"
#include <vector>
#include <cstdint>
#include "MediaEngine/Include/Core/PlatformDetection.h"

#ifdef ME_PLATFORM_WINDOWS
#define VK_USE_PLATFORM_WIN32_KHR
#elif defined(ME_PLATFORM_MACOS)
// todo
#else
#error "Unsupport Plarform"
#endif  // PLATFORM_WINDOWS
#include "vulkan/vulkan.h"

#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include "ThirdParty/glfw-3.4/include/GLFW/glfw3.h"

#include "MediaEngine/Include/Core/Ptr.h"
#include "VulkanRHIResources.h"
#include "VulkanRHITexture.h"

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
    virtual Ref<RHITexture2D> GetCurrentBackTexture() override;
    virtual RHISwapchainInfo GetSwapchainInfo() override;

    // ImGui
    virtual void* CreateImTextureID(Ref<RHITexture2D> texture) override;
    virtual void DestroyImTextureID(void* imTextureID) override;

    // Resources
    virtual Ref<RHIBuffer> CreateRHIBuffer(RHIBufferCreateDesc createDesc) override;
    virtual Ref<RHITexture2D> CreateRHITexture2D(RHITexture2DCreateDesc desc) override;
    virtual Ref<RHIRenderPass> CreateRHIRenderPass(RHIRenderPassCreateDesc desc) override;
    virtual Ref<RHIFramebuffer> CreateRHIFramebuffer(
        uint32_t width,
        uint32_t height,
        Ref<RHIRenderPass> renderPass,
        std::vector<Ref<RHITexture2D>>& textures) override;
    virtual Ref<RHIShader> CreateRHIShader(RHIShaderCreateInfo createInfo) override;
    virtual Ref<RHIDescriptorSet> CreateRHIDescriptorSet(RHIDescriptorSetCreateInfo createInfo) override;
    virtual Ref<RHIGraphicPipeline> CreateGraphicPipeline(RHIGraphicPipelineCreateInfo createInfo) override;

    virtual void UpdateDescriptorSets(
        Ref<RHIDescriptorSet> RelateDescriptorSet,
        const std::vector<RHIWriteDescriptorSet>& writesDescSets) override;

    virtual void DestroyRHITexture2D(Ref<RHITexture2D> texture) override;
    virtual void DestroyRHIRenderPass(Ref<RHIRenderPass> renderPass) override;
    virtual void DestroyRHIFramebuffer(Ref<RHIFramebuffer> framebuffer) override;

    // Command
    virtual bool BeginCommandBuffer(Ref<RHICommandBuffer> cmdBuffer) override;
    virtual bool EndCommandBuffer(Ref<RHICommandBuffer> cmdBuffer) override;
    virtual void CmdPushEvent(Ref<RHICommandBuffer> cmdBuffer, const char* name, RHIColor color) override;
    virtual void CmdPopEvent(Ref<RHICommandBuffer> cmdBuffer) override;
    virtual void CmdBeginRenderPass(Ref<RHICommandBuffer> cmdBuffer, RHIRenderPassBeginInfo beginIhfo) override;
    virtual void CmdEndRenderPass(Ref<RHICommandBuffer> cmdBuffer) override;
    virtual void CmdClearColor(Ref<RHICommandBuffer> cmdBuffer, Ref<RHITexture2D> texture, RHIColor color) override;
    virtual void CmdPipelineBarrier(Ref<RHICommandBuffer> cmdBuffer, RHIPipelineBarrierInfo barrierInfo) override;
    virtual void CmdCopyTexture(Ref<RHICommandBuffer> cmdBuffer, Ref<RHITexture2D> src, Ref<RHITexture2D> dst) override;
    virtual void CmdBindGraphicPipeline(Ref<RHICommandBuffer> cmdBuffer, Ref<RHIGraphicPipeline> pipeline) override;
    virtual void CmdSetViewport(Ref<RHICommandBuffer> cmdBuffer, RHIViewport viewport) override;
    virtual void CmdSetScissor(Ref<RHICommandBuffer> cmdBuffer, RHIScissor scissor) override;
    virtual void CmdBindVertexBuffer(Ref<RHICommandBuffer> cmdBuffer, Ref<RHIBuffer> buffer) override;
    virtual void CmdBindIndexBuffer(Ref<RHICommandBuffer> cmdBuffer, Ref<RHIBuffer> buffer) override;
    virtual void CmdBindDescriptorSets(Ref<RHICommandBuffer> cmdBuffer, Ref<RHIGraphicPipeline> pipeline) override;
    virtual void CmdBindDescriptorSets(
        Ref<RHICommandBuffer> cmdBuffer,
        Ref<RHIGraphicPipeline> pipeline,
        const std::vector<Ref<RHIDescriptorSet>> descriptorSets) override;
    virtual void CmdCopyBufferToImage(Ref<RHICommandBuffer> cmdBuffer, Ref<RHIBuffer> buffer, Ref<RHITexture2D> texture)
        override;
    virtual void CmdPushConstants(
        Ref<RHICommandBuffer> cmdBuffer,
        Ref<RHIGraphicPipeline> pipeline,
        ERHIShaderStage shaderStage,
        uint32_t offset,
        uint32_t size,
        const void* data) override;
    virtual void CmdDrawIndexed(
        Ref<RHICommandBuffer> cmdBuffer,
        uint32_t indexCount,
        uint32_t instanceCount,
        uint32_t firstIndex,
        int32_t vertexOffset,
        uint32_t firstInstance) override;

public:
    struct VulkanQueue
    {
        VkQueue Queue = VK_NULL_HANDLE;
        uint32_t QueueFamilyIndex = UINT32_MAX;
    };

    VkInstance GetInstance();
    VkPhysicalDevice GetPhysicalDevice();
    VkDevice GetDevice();
    VulkanQueue GetGraphicQueue();
    VkDescriptorPool GetDescriptorPool();
    uint32_t GetMinImageCount();
    uint32_t GetBackImageCount();

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
    VkExtent2D GetSwapchainExtend(VkPhysicalDevice device, VkSurfaceKHR surface, uint32_t wndWidth, uint32_t wndHeight);
    bool CreateSwapchainResources(
        VkSwapchainKHR& swapchain,
        std::vector<Ref<VulkanRHITexture2D>>& swapchainTextures,
        std::vector<VkSemaphore>& imageAcquiredSemaphores,
        std::vector<VkSemaphore>& renderCompleteSemaphores,
        VkPhysicalDevice physicalDevie,
        VkDevice device,
        VulkanQueue graphicQueue,
        VulkanQueue presentQueue,
        VkSurfaceKHR surface,
        VkExtent2D extend,
        uint32_t minImageCount);
    VkDescriptorPool CreateDescriptorPool(VkDevice device);
    VkSampler CreateSampler(VkDevice device);

private:
    struct ShaderSpv
    {
        std::vector<uint32_t> Code;
        uint32_t CodeSize = 0;
    };

    ShaderSpv CreateSPIRVFromFile(const std::string& path, ERHIShaderType shaderType);

    uint32_t FindMemoryIndex(VkMemoryPropertyFlags requiredFlags, VkDeviceSize size);

private:
    VkInstance m_Instance = VK_NULL_HANDLE;
    VkSurfaceKHR m_Surface = VK_NULL_HANDLE;
    VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
    VkDevice m_Device = VK_NULL_HANDLE;

    VkDescriptorPool m_DescriptorPool = VK_NULL_HANDLE;
    VulkanQueue m_GraphicQueue;
    VulkanQueue m_PresentQueue;
    VulkanQueue m_ComputeQueue;
    VkCommandPool m_CommandPool = VK_NULL_HANDLE;
    Ref<VulkanRHICommandBuffer> m_RHICommandBuffer;
    VkFence m_FenceForCommandBuffer = VK_NULL_HANDLE;

    const uint32_t m_MinImageCount = 2;
    VkSwapchainKHR m_Swapchain = VK_NULL_HANDLE;
    VkExtent2D m_SwapchainExtend = {0, 0};
    std::vector<Ref<VulkanRHITexture2D>> m_SwapchainTextures;
    uint32_t m_SwapchainFrameIndex = 0;
    std::vector<VkSemaphore> m_ImageAcquiredSemaphores;
    std::vector<VkSemaphore> m_RenderCompleteSemaphores;
    uint32_t m_GraphicSemaphoreCnt = 0;
    uint32_t m_GraphicSemaphoreIndex = 0;
    VkSampler m_Sampler = VK_NULL_HANDLE;
    VkPhysicalDeviceMemoryProperties m_MemoryProperties;

private:
    PFN_vkCmdBeginDebugUtilsLabelEXT m_VkCmdBeginDebugUtilsLabelEXT = nullptr;
    PFN_vkCmdEndDebugUtilsLabelEXT m_VkCmdEndDebugUtilsLabelEXT = nullptr;
};

}  //namespace ME
