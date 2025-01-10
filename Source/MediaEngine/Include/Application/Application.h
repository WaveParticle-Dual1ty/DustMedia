#pragma once
#include <memory>
#include <string>
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
    void OnEvent(Event& event);
    bool OnWindowClosed(WindowCloseEvent& event);
    bool OnWindowResize(WindowResizeEvent& event);

private:
    ApplicationSpecification m_AppSpec;
    bool m_Running = true;

    std::shared_ptr<Window> m_Window;
};

std::unique_ptr<Application> CreateApplication();

}  //namespace ME