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
    return std::make_unique<DustImageViewerApp>();
}

DustImageViewerApp::DustImageViewerApp()
    : Application({"Dust Image Viewer"})
{
}

bool DustImageViewerApp::OnEngineInit()
{
    ME::Ref<EditorLayer> editorLayer = ME::CreateRef<EditorLayer>();
    PushLayer(editorLayer);

    return true;
}
