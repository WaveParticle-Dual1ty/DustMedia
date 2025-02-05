#include "DustImageViewerApp.h"
#include <memory>
#include <iostream>
#include <filesystem>
#include "MediaEngine/Include/Core/Ptr.h"
#include "MediaEngine/Include/Application/EntryPoint.h"
#include "MediaEngine/Include/Application/Application.h"
#include "EditorLayer.h"

std::unique_ptr<ME::Application> ME::CreateApplication()
{
    std::filesystem::path binPath = std::filesystem::current_path();
    std::filesystem::path resourcePath = binPath / "Resources/DustImageViewer";
    resourcePath = std::filesystem::absolute(resourcePath);
    return std::make_unique<DustImageViewerApp>(binPath.string(), resourcePath.string());
}

DustImageViewerApp::DustImageViewerApp(const std::string& binPath, const std::string& resourcePath)
    : Application({"Dust Image Viewer", binPath, resourcePath})
{
}

bool DustImageViewerApp::OnEngineInit()
{
    ME::Ref<EditorLayer> editorLayer = ME::CreateRef<EditorLayer>();
    PushLayer(editorLayer);

    return true;
}
