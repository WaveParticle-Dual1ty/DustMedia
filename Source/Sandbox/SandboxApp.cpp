#include "SandboxApp.h"
#include <memory>
#include <iostream>
#include "MediaEngine/Include/Core/Core.h"
#include "MediaEngine/Include/Application/EntryPoint.h"
#include "MediaEngine/Include/Application/Application.h"
#include "DebugLayer.h"
#include "TestLayer.h"

std::unique_ptr<ME::Application> ME::CreateApplication()
{
    return std::make_unique<SandboxApp>();
}

SandboxApp::SandboxApp()
    : Application({"Sandbox"})
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
