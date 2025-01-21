#pragma once
#include "vulkan/vulkan.h"
#include "../ImGuiLayer.h"

namespace ME
{
class VulkanImGuiLayer : public ImGuiLayer
{
public:
    VulkanImGuiLayer();

public:
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(Timestep timestep) override;
    virtual void OnUIUpdate() override;
    virtual void OnEvent(Event& event) override;

    virtual bool Init(Ref<Window> wnd, Ref<RHI> rhi, Ref<RHIRenderPass> rhiRenderPass) override;
    virtual void Begin() override;
    virtual void End() override;

private:
    static void CheckVkResult(VkResult err);
};

}  //namespace ME