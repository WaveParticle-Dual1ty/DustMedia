#pragma once
#include <iostream>
#include "MediaEngine/Include/Core/Core.h"
#include "MediaEngine/Include/Application/EntryPoint.h"
#include "MediaEngine/Include/Application/Application.h"

class EmptyApp : public ME::Application
{
public:
    EmptyApp();

private:
    virtual bool OnEngineInit() override;
};
