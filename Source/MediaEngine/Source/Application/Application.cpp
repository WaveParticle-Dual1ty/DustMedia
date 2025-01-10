#include "MediaEngine/Include/Application/Application.h"
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

void Application::OnEvent(Event& event)
{
}

}  //namespace ME