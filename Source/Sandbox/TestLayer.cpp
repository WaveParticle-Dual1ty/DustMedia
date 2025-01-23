#include "TestLayer.h"
#include "ThirdParty/imgui/imgui.h"
#include "MediaEngine/Include/Core/Assert.h"
#include "MediaEngine/Include/Application/Application.h"
#include "MediaEngine/Include/Event/MouseEvent.h"
#include "MediaEngine/Include/Event/Input.h"
#include "MediaEngine/Include/Event/EventUtils.h"

TestLayer::TestLayer()
    : Layer("TestLayer")
{
}

void TestLayer::OnAttach()
{
    m_RHI = Application::Get().GetRHI();
    m_TestRenderPass = CreateRef<TestRenderPass>(m_RHI);
    bool ret = m_TestRenderPass->Initialize(300, 200);
    if (!ret)
    {
        ME_ASSERT(false, "TestRenderPass::Initialize fail");
        return;
    }
}

void TestLayer::OnDetach()
{
}

void TestLayer::OnUpdate(ME::Timestep timestep)
{
    //Ref<RHICommandBuffer> cmdBuffer = m_RHI->GetCurrentCommandBuffer();
}

void TestLayer::OnUIUpdate()
{
    ImGui::Begin("TestLayer");

    ImGui::End();
}

void TestLayer::OnEvent(ME::Event& event)
{
}
