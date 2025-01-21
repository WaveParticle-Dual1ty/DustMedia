#include "VulkanImGuiLayer.h"
#include "ThirdParty/imgui/imgui.h"
#include "ThirdParty/imgui/backends/imgui_impl_glfw.h"
#include "ThirdParty/imgui/backends/imgui_impl_vulkan.h"
#include "ThirdParty/glfw-3.4/include/GLFW/glfw3.h"
#include "MediaEngine/Source/Render/Vulkan/VulkanRHI.h"
#include "MediaEngine/Source/Render/Vulkan/VulkanRHIResources.h"
#include "../ImGuiLog.h"

namespace ME
{
VulkanImGuiLayer::VulkanImGuiLayer()
    : ImGuiLayer("VulkanImGuiLayer")
{
}

void VulkanImGuiLayer::OnAttach()
{
}

void VulkanImGuiLayer::OnDetach()
{
}

void VulkanImGuiLayer::OnUpdate(Timestep timestep)
{
}

void VulkanImGuiLayer::OnUIUpdate()
{
    bool showDemoWindow = true;
    if (showDemoWindow)
        ImGui::ShowDemoWindow(&showDemoWindow);
}

void VulkanImGuiLayer::OnEvent(Event& event)
{
}

bool VulkanImGuiLayer::Init(Ref<Window> wnd, Ref<RHI> rhi, Ref<RHIRenderPass> rhiRenderPass)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    Ref<VulkanRHI> vulkanRHI = std::dynamic_pointer_cast<VulkanRHI>(rhi);
    Ref<VulkanRHIRenderPass> vulkanRHIRenderPass = std::dynamic_pointer_cast<VulkanRHIRenderPass>(rhiRenderPass);
    GLFWwindow* glfwWnd = (GLFWwindow*)wnd->GetNativeWindow();

    bool ret = ImGui_ImplGlfw_InitForVulkan(glfwWnd, true);
    if (!ret)
    {
        IMGUI_LOG_ERROR("ImGui_ImplGlfw_InitForVulkan fail");
        return false;
    }

    ImGui_ImplVulkan_InitInfo initInfo = {};
    initInfo.Instance = vulkanRHI->GetInstance();
    initInfo.PhysicalDevice = vulkanRHI->GetPhysicalDevice();
    initInfo.Device = vulkanRHI->GetDevice();
    initInfo.QueueFamily = vulkanRHI->GetGraphicQueue().QueueFamilyIndex;
    initInfo.Queue = vulkanRHI->GetGraphicQueue().Queue;
    initInfo.PipelineCache = VK_NULL_HANDLE;
    initInfo.DescriptorPool = vulkanRHI->GetDescriptorPool();
    initInfo.RenderPass = vulkanRHIRenderPass->RenderPass;
    initInfo.Subpass = 0;
    initInfo.MinImageCount = vulkanRHI->GetMinImageCount();
    initInfo.ImageCount = vulkanRHI->GetBackImageCount();
    initInfo.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
    initInfo.Allocator = nullptr;
    initInfo.CheckVkResultFn = CheckVkResult;
    ret = ImGui_ImplVulkan_Init(&initInfo);
    if (!ret)
    {
        IMGUI_LOG_ERROR("ImGui_ImplVulkan_Init fail");
        return false;
    }

    return true;
}

void VulkanImGuiLayer::Begin()
{
    ImGui_ImplVulkan_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void VulkanImGuiLayer::End()
{
    ImGui::Render();

    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
}

void VulkanImGuiLayer::CheckVkResult(VkResult err)
{
    if (err == 0)
        return;

    IMGUI_LOG_ERROR("[vulkan] Error: VkResult = {}", (int)err);

    if (err < 0)
        abort();
}

}  //namespace ME