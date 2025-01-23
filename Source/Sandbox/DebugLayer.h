#pragma once
#include <iostream>
#include <string>
#include <array>
#include "MediaEngine/Include/Application/Layer.h"
#include "MediaEngine/Include/Event/MouseEvent.h"
#include "MediaEngine/Include/Event/KeyEvent.h"
#include "MediaEngine/Include/Event/ApplicationEvent.h"

class DebugLayer : public ME::Layer
{
public:
    DebugLayer();

public:
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(ME::Timestep timestep) override;
    virtual void OnUIUpdate() override;
    virtual void OnEvent(ME::Event& event) override;

private:
    bool OnMouseMovedEvent(ME::MouseMovedEvent& event);
    bool OnKeyPressedEvent(ME::KeyPressedEvent& event);
    bool OnMouseButtonPressedEvent(ME::MouseButtonPressedEvent& event);
    bool OnWindowResizeEvent(ME::WindowResizeEvent& event);
    bool OnFileDropEvent(ME::FileDropEvent& event);

private:
    ME::Timestep m_Timestep;
    std::array<float, 2> m_MousePos = {0, 0};
    std::array<uint32_t, 2> m_WndSize = {0, 0};
    ME::KeyCode m_PressKey = ME::KeyCode::Unknow;
    ME::MouseCode m_PressMouse = ME::MouseCode::Unkown;
    std::vector<std::string> m_DropFiles;
};
