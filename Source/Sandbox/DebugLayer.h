#pragma once
#include <iostream>
#include <string>
#include <array>
#include "MediaEngine/Include/Application/Layer.h"
#include "MediaEngine/Include/Event/MouseEvent.h"

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

private:
    std::array<float, 2> m_MousePos = {0};
};
