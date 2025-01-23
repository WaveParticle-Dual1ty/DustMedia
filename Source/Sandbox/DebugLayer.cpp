#include "DebugLayer.h"
#include "ThirdParty/imgui/imgui.h"
#include "MediaEngine/Include/Application/Application.h"
#include "MediaEngine/Include/Event/MouseEvent.h"
#include "MediaEngine/Include/Event/Input.h"
#include "MediaEngine/Include/Event/EventUtils.h"

DebugLayer::DebugLayer()
    : Layer("DebugLayer")
{
}

void DebugLayer::OnAttach()
{
    ME::Window& wnd = ME::Application::Get().GetWindow();
    m_WndSize = {wnd.GetWidth(), wnd.GetHeight()};
}

void DebugLayer::OnDetach()
{
}

void DebugLayer::OnUpdate(ME::Timestep timestep)
{
    m_Timestep = timestep;
}

void DebugLayer::OnUIUpdate()
{
    ImGui::Begin("DebugLayer");

    float timestepInMS = m_Timestep.GetMilliseconds();
    float fps = 1000 / timestepInMS;
    ImGui::Text("Application %.3fms/frame (%.3fFPS)", timestepInMS, fps);

    bool inputsOpened = ImGui::TreeNode("Inputs");
    if (inputsOpened)
    {
        float x = ME::Input::GetMouseX();
        float y = ME::Input::GetMouseY();

        ImGui::Text("Mouse pos: (%g, %g)", x, y);
        ImGui::TreePop();
    }

    bool eventsOpened = ImGui::TreeNode("Events");
    if (eventsOpened)
    {
        ImGui::Text("Window size: (%d, %d)", m_WndSize[0], m_WndSize[1]);
        ImGui::Text("Mouse pos: (%g, %g)", m_MousePos[0], m_MousePos[1]);
        ImGui::Text("Key pressed: %s", ME::Util::KeyCodeInStr(m_PressKey));
        ImGui::Text("Mouse pressed: %s", ME::Util::MouseCodeInStr(m_PressMouse));

        ImGui::Text("Drop files: ");
        if (!m_DropFiles.empty())
        {
            for (auto& filePath : m_DropFiles)
            {
                ImGui::Text("\t%s", filePath.c_str());
            }
        }

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

    dispatcher.Dispatch<ME::KeyPressedEvent>(
        [this](ME::KeyPressedEvent& event) -> bool
        {
            return OnKeyPressedEvent(event);
        });

    dispatcher.Dispatch<ME::MouseButtonPressedEvent>(
        [this](ME::MouseButtonPressedEvent& event) -> bool
        {
            return OnMouseButtonPressedEvent(event);
        });

    dispatcher.Dispatch<ME::WindowResizeEvent>(
        [this](ME::WindowResizeEvent& event) -> bool
        {
            return OnWindowResizeEvent(event);
        });

    dispatcher.Dispatch<ME::FileDropEvent>(
        [this](ME::FileDropEvent& event) -> bool
        {
            return OnFileDropEvent(event);
        });
}

bool DebugLayer::OnMouseMovedEvent(ME::MouseMovedEvent& event)
{
    float x = event.GetX();
    float y = event.GetY();
    m_MousePos = {x, y};
    return false;
}

bool DebugLayer::OnKeyPressedEvent(ME::KeyPressedEvent& event)
{
    m_PressKey = event.GetKeyCode();
    return false;
}

bool DebugLayer::OnMouseButtonPressedEvent(ME::MouseButtonPressedEvent& event)
{
    m_PressMouse = event.GetMouseButton();
    return false;
}

bool DebugLayer::OnWindowResizeEvent(ME::WindowResizeEvent& event)
{
    uint32_t w = event.GetWidth();
    uint32_t h = event.GetHeight();
    m_WndSize = {w, h};
    return false;
}

bool DebugLayer::OnFileDropEvent(ME::FileDropEvent& event)
{
    m_DropFiles = event.GetDropFiles();
    return false;
}
