#pragma once
#include <memory>
#include <string>
#include "MediaEngine/Include/Core/Timestep.h"
#include "MediaEngine/Include/Window/Window.h"
#include "MediaEngine/Include/Event/ApplicationEvent.h"

namespace ME
{
struct ApplicationSpecification
{
    std::string Name = "Application";
};

class Application
{
public:
    Application(const ApplicationSpecification& spec);
    virtual ~Application() = default;

public:
    void Run();

private:
    bool InitApp();
    Timestep GetTimestep();
    void OnEvent(Event& event);
    bool OnWindowClosed(WindowCloseEvent& event);
    bool OnWindowResize(WindowResizeEvent& event);

private:
    ApplicationSpecification m_AppSpec;
    bool m_Running = true;
    double m_LastFrameTimeInSec = 0.f;

    std::shared_ptr<Window> m_Window;
};

std::unique_ptr<Application> CreateApplication();

}  //namespace ME