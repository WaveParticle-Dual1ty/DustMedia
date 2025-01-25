#include "TestLayer.h"
#include <array>
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
    Ref<RHICommandBuffer> cmdBuffer = m_RHI->GetCurrentCommandBuffer();
    //m_RHI->BeginCommandBuffer(cmdBuffer);
    m_TestRenderPass->Draw(cmdBuffer);
    //m_RHI->EndCommandBuffer(cmdBuffer);
}

void TestLayer::OnUIUpdate()
{
    ImGui::Begin("TestLayer");

    static std::array<float, 4> color = {0, 0, 0, 1};
    ImGui::ColorEdit4("Color", color.data());
    m_TestRenderPass->SetColor(color);

    void* texID = m_TestRenderPass->GetTargetImTextureID();
    ImGui::Image(texID, ImVec2(300, 200), ImVec2(0, 1), ImVec2(1, 0));

    ImGui::End();
}

void TestLayer::OnEvent(ME::Event& event)
{
}
