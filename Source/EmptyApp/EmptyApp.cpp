#include "EmptyApp.h"
#include <memory>
#include <iostream>
#include <filesystem>
#include "MediaEngine/Include/Core/Core.h"
#include "MediaEngine/Include/Application/EntryPoint.h"
#include "MediaEngine/Include/Application/Application.h"

std::unique_ptr<ME::Application> ME::CreateApplication()
{
    return std::make_unique<EmptyApp>();
}

EmptyApp::EmptyApp()
    : Application({"EmptyApp"})
{
}

bool EmptyApp::OnEngineInit()
{
    return true;
}
