﻿#include "EditorLayer.h"
#include <array>
#include "ThirdParty/imgui/imgui.h"
#include "MediaEngine/Include/Core/Assert.h"
#include "MediaEngine/Include/Application/Application.h"
#include "DustImageViewerLog.h"

EditorLayer::EditorLayer()
    : Layer("EditorLayer")
{
}

void EditorLayer::OnAttach()
{
}

void EditorLayer::OnDetach()
{
}

void EditorLayer::OnUpdate(ME::Timestep timestep)
{
    static_cast<void>(timestep);
}

void EditorLayer::OnUIUpdate()
{
    BeginDockspace();

    // Information
    ImGui::Begin("Information");

    if (m_CurrentImage != nullptr)
    {
        if (ImGui::CollapsingHeader("File", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Text("File path: %s", m_CurrentImage->GetFilePath().c_str());
        }

        if (ImGui::CollapsingHeader("Image", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Text("Width:  \t%d", m_CurrentImage->GetWidth());
            ImGui::Text("Height: \t%d", m_CurrentImage->GetHeight());
        }
    }

    ImGui::End();

    // Viewport
    ImGui::Begin("Viewport");

    ImGui::End();

    // ImGui Demo
    bool showDemoWnd = true;
    if (showDemoWnd)
        ImGui::ShowDemoWindow(&showDemoWnd);

    EndDockspace();
}

void EditorLayer::OnEvent(ME::Event& event)
{
    ME::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<ME::FileDropEvent>(
        [this](ME::FileDropEvent& event) -> bool
        {
            return OnFileDrop(event);
        });
}

void EditorLayer::BeginDockspace()
{
    static bool dockspaceOpen = true;
    static bool optFullscreen = true;
    static bool optPadding = false;
    static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (optFullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                       ImGuiWindowFlags_NoMove;
        windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        dockspaceFlags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
    // and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode)
        windowFlags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    if (!optPadding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &dockspaceOpen, windowFlags);
    if (!optPadding)
        ImGui::PopStyleVar();

    if (optFullscreen)
        ImGui::PopStyleVar(2);

    // Submit the DockSpace
    ImGuiIO& io = ImGui::GetIO();
    ImGuiStyle& style = ImGui::GetStyle();
    //float minWinSizeX = style.WindowMinSize.x;
    style.WindowMinSize.x = 370.f;
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspaceFlags);
    }
}

void EditorLayer::EndDockspace()
{
    ImGui::End();
}

bool EditorLayer::OnFileDrop(ME::FileDropEvent& event)
{
    std::string imagePath = event.GetDropFiles()[0];
    m_CurrentImage = ME::CreateRef<ME::ImageLoader>();
    bool ret = m_CurrentImage->Load(imagePath);
    if (!ret)
    {
        IMAGEVIWER_LOG_WARN("Fail to load image: {}", imagePath);
        m_CurrentImage = nullptr;
        return false;
    }

    return false;
}
