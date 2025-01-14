﻿#include "MediaEngine/Include/Application/Application.h"
#include <thread>
#include <chrono>
#include "MediaEngine/Include/Core/Time.h"
#include "AppLog.h"
#include "LayerStack.h"

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

        m_Window->PollEvents();

        if (m_WndMinimized)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        if (m_WndResized)
        {
            m_WndResized = false;

            uint32_t w = m_Window->GetWidth();
            uint32_t h = m_Window->GetHeight();
            ret = m_RHI->Resize(w, h);
            if (!ret)
            {
                APP_LOG_ERROR("RHI::Resize fail");
                break;
            }
        }

        m_RHI->PrepareForNextFrame();

        m_RHI->BeginCommandBuffer(m_RHI->GetCurrentCommandBuffer());
        m_RHI->ClearBackBuffer(m_RHI->GetCurrentCommandBuffer(), 0.1, 0.2, 0.3, 1);
        m_RHI->EndCommandBuffer(m_RHI->GetCurrentCommandBuffer());

        m_RHI->SubmmitRenderCommands();
        m_RHI->Present();
    }

    m_Window->Destroy();

    APP_LOG_INFO("Application stop");
}

void Application::PushLayer(std::shared_ptr<Layer> layer)
{
    m_LayerStack->PushLayer(layer);
}

void Application::PushOverlay(std::shared_ptr<Layer> layer)
{
    m_LayerStack->PushOverlay(layer);
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

    m_LayerStack = std::make_shared<LayerStack>();

    ret = OnEngineInit();
    if (!ret)
    {
        APP_LOG_ERROR("OnEngineInit fail");
        return false;
    }

    m_RHI = RHI::CreateRHI(RHI::API::Vulkan);
    ret = m_RHI->Initialize(m_Window);
    if (!ret)
    {
        APP_LOG_ERROR("RHI::Initialize fail");
        return false;
    }

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

    const LayerStack::LayerList& layers = m_LayerStack->GetLayers();
    for (auto it = layers.rbegin(); it != layers.rend(); ++it)
    {
        const std::shared_ptr<Layer>& layer = *it;
        layer->OnEvent(event);
        if (event.Handled)
            break;
    }
}

bool Application::OnWindowClosed(WindowCloseEvent& event)
{
    APP_LOG_INFO("Application receive event: {}", event.ToString());
    m_Running = false;
    return false;
}

bool Application::OnWindowResize(WindowResizeEvent& event)
{
    if (event.GetWidth() == 0 || event.GetHeight() == 0)
    {
        APP_LOG_INFO("Application receive minimized event");
        m_WndMinimized = true;
        return false;
    }
    else
    {
        m_WndMinimized = false;
        m_WndResized = true;
        return false;
    }

    return false;
}

void Application::UpdateLayers(Timestep timestep)
{
    for (const auto& layer : m_LayerStack->GetLayers())
    {
        layer->OnUpdate(timestep);
    }
}

void Application::UpdateLayersUI(Timestep timestep)
{
    if (m_EnableUI)
    {
    }
}

}  //namespace ME