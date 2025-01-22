#include "DebugLayer.h"
#include "ThirdParty/imgui/imgui.h"
#include "MediaEngine/Include/Event/MouseEvent.h"

DebugLayer::DebugLayer()
    : Layer("DebugLayer")
{
}

void DebugLayer::OnAttach()
{
}

void DebugLayer::OnDetach()
{
}

void DebugLayer::OnUpdate(ME::Timestep timestep)
{
}

void DebugLayer::OnUIUpdate()
{
    ImGui::Begin("DebugLayer");

    bool inputsOpened = ImGui::TreeNode("Inputs");
    if (inputsOpened)
    {
        ImGui::Text("Mouse pos: (%g, %g)", m_MousePos[0], m_MousePos[1]);
        ImGui::TreePop();
    }

    ImGui::End();
}

void DebugLayer::OnEvent(ME::Event& event)
{
    ME::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<ME::MouseMovedEvent>(
        [this](ME::MouseMovedEvent& event) -> bool
        {
            return OnMouseMovedEvent(event);
        });
}

bool DebugLayer::OnMouseMovedEvent(ME::MouseMovedEvent& event)
{
    float x = event.GetX();
    float y = event.GetY();
    m_MousePos = {x, y};
    return false;
}
