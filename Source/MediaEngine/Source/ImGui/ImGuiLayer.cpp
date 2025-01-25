#include "ImGuiLayer.h"
#include "MediaEngine/Include/Core/Assert.h"
#include "Vulkan/VulkanImGuiLayer.h"

namespace ME
{
ImGuiLayer::ImGuiLayer(const std::string& name)
    : Layer(name)
{
}

Ref<ImGuiLayer> ImGuiLayer::Create(RHI::API api)
{
    if (api == RHI::API::Vulkan)
    {
        auto res = CreateRef<VulkanImGuiLayer>();
        return res;
    }
    else
    {
        ME_ASSERT(false, "Not support this render API");
        return nullptr;
    }
}

}  //namespace ME