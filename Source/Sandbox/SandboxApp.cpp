#include "SandboxApp.h"
#include <memory>
#include <iostream>
#include <filesystem>
#include "MediaEngine/Include/Core/Core.h"
#include "MediaEngine/Include/Application/EntryPoint.h"
#include "MediaEngine/Include/Application/Application.h"
#include "DebugLayer.h"
#include "TestLayer.h"

std::unique_ptr<ME::Application> ME::CreateApplication()
{
    std::filesystem::path binPath = std::filesystem::current_path();
    std::filesystem::path resourcePath = binPath / "Resources/Sandbox";
    resourcePath = std::filesystem::absolute(resourcePath);
    return std::make_unique<SandboxApp>(binPath.string(), resourcePath.string());
}

SandboxApp::SandboxApp(const std::string& binPath, const std::string& resourcePath)
    : Application({"Sandbox", binPath, resourcePath})
{
}

bool SandboxApp::OnEngineInit()
{
    std::shared_ptr<DebugLayer> debugLayer = std::make_shared<DebugLayer>();
    std::shared_ptr<TestLayer> testLayer = std::make_shared<TestLayer>();
    PushLayer(debugLayer);
    PushLayer(testLayer);

    return true;
}
