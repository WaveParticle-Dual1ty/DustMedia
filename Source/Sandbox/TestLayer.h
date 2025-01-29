#pragma once
#include <iostream>
#include <string>
#include <array>
#include "MediaEngine/Include/Application/Layer.h"
#include "MediaEngine/Include/Event/MouseEvent.h"
#include "MediaEngine/Include/Event/KeyEvent.h"
#include "MediaEngine/Include/Event/ApplicationEvent.h"
#include "TestRenderPass.h"

class TestLayer : public ME::Layer
{
public:
    TestLayer();

public:
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(ME::Timestep timestep) override;
    virtual void OnUIUpdate() override;
    virtual void OnEvent(ME::Event& event) override;

private:
    void BeginDockspace();
    void EndDockspace();

private:
    Ref<RHI> m_RHI;
    Ref<TestRenderPass> m_TestRenderPass;
    std::array<uint32_t, 2> m_ViewportSize = {0, 0};
    std::array<uint32_t, 2> m_CacheViewportSize = {0, 0};
};
