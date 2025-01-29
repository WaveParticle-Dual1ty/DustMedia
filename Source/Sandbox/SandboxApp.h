#pragma once
#include <iostream>
#include "MediaEngine/Include/Core/Core.h"
#include "MediaEngine/Include/Application/EntryPoint.h"
#include "MediaEngine/Include/Application/Application.h"

class SandboxApp : public ME::Application
{
public:
    SandboxApp(const std::string& binPath, const std::string& resourcePath);

private:
    virtual bool OnEngineInit() override;
};
