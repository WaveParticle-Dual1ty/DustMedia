#pragma once
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

    virtual void Begin() override;
    virtual void End() override;
};

}  //namespace ME