#pragma once
#include <iostream>
#include "MediaEngine/Include/Core/Core.h"
#include "MediaEngine/Include/Application/EntryPoint.h"
#include "MediaEngine/Include/Application/Application.h"

class DustImageViewerApp : public ME::Application
{
public:
    DustImageViewerApp();

private:
    virtual bool OnEngineInit() override;
};
