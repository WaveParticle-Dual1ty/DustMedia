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

    m_ViewportSize = {300, 200};
    m_CacheViewportSize = m_ViewportSize;
}

void TestLayer::OnDetach()
{
}

void TestLayer::OnUpdate(ME::Timestep timestep)
{
    std::array<uint32_t, 2> size = m_CacheViewportSize;
    if (size[0] != m_ViewportSize[0] || size[1] != m_ViewportSize[1])
    {
        m_ViewportSize = size;
        m_TestRenderPass->Resize(size[0], size[1]);
    }

    Ref<RHICommandBuffer> cmdBuffer = m_RHI->GetCurrentCommandBuffer();
    m_TestRenderPass->Draw(cmdBuffer);
}

void TestLayer::OnUIUpdate()
{
    ImVec2 viewportSize = ImVec2(0, 0);

    {
        ImGui::Begin("Viewport");

        viewportSize = ImGui::GetContentRegionAvail();
        m_CacheViewportSize = {(uint32_t)viewportSize.x, (uint32_t)viewportSize.y};

        void* texID = m_TestRenderPass->GetTargetImTextureID();
        ImGui::Image(texID, ImVec2(viewportSize.x, viewportSize.y), ImVec2(0, 1), ImVec2(1, 0));

        ImGui::End();
    }

    {
        ImGui::Begin("Edit");

        static std::array<float, 4> color = {0, 0, 0, 1};
        ImGui::ColorEdit4("Color", color.data());
        m_TestRenderPass->SetColor(color);

        ImGui::Text("Viewport size: (%.2f, %.2f)", viewportSize.x, viewportSize.y);

        ImGui::End();
    }
}

void TestLayer::OnEvent(ME::Event& event)
{
}
