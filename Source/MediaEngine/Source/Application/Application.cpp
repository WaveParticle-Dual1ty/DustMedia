#include "MediaEngine/Include/Application/Application.h"
#include "MediaEngine/Include/Core/Time.h"
#include "AppLog.h"

namespace ME
{
Application::Application(const ApplicationSpecification& spec)
    : m_AppSpec(spec)
{
}

void Application::Run()
{
    bool ret = InitApp();
    if (!ret)
    {
        APP_LOG_ERROR("InitApp fail");
        return;
    }

    while (m_Running)
    {
        Timestep timestep = GetTimestep();
        //APP_LOG_INFO("Timestep: {}ms", timestep.GetMilliseconds());

        m_Window->PollEvents();
    }

    m_Window->Destroy();

    APP_LOG_INFO("Application stop");
}

bool Application::InitApp()
{
    WindowProps props;
    props.Title = m_AppSpec.Name;
    props.Width = 1500;
    props.Height = 800;

    m_Window = Window::Create();
    bool ret = m_Window->InitWindow(props);
    if (!ret)
    {
        APP_LOG_ERROR("Window::InitWindow fail");
        return false;
    }

    m_Window->SetEventCallback(
        [this](Event& event)
        {
            OnEvent(event);
        });

    return true;
}

Timestep Application::GetTimestep()
{
    float time = Time::GetCurrentTimeInSecond();
    Timestep timestep = time - m_LastFrameTimeInSec;
    m_LastFrameTimeInSec = time;
    return timestep;
}

void Application::OnEvent(Event& event)
{
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<WindowCloseEvent>(
        [this](WindowCloseEvent& event) -> bool
        {
            return OnWindowClosed(event);
        });

    dispatcher.Dispatch<WindowResizeEvent>(
        [this](WindowResizeEvent& event) -> bool
        {
            return OnWindowResize(event);
        });
}

bool Application::OnWindowClosed(WindowCloseEvent& event)
{
    APP_LOG_INFO("Application recieve event: {}", event.ToString());
    m_Running = false;
    return false;
}

bool Application::OnWindowResize(WindowResizeEvent& event)
{
    return false;
}

}  //namespace ME