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

    virtual bool Init(const std::string& iniFilename, Ref<Window> wnd, Ref<RHI> rhi, Ref<RHIRenderPass> renderPass)
        override;
    virtual void Begin() override;
    virtual void End() override;

private:
    static void CheckVkResult(VkResult err);

private:
    std::string m_IniFile;
};

}  //namespace ME