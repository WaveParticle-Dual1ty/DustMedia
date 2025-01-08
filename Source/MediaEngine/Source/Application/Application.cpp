#include "MediaEngine/Include/Application/Application.h"
#include "AppLog.h"

namespace ME
{
void Application::Run()
{
    while (m_Running)
    {
        APP_LOG_INFO("Application running");
    }

    APP_LOG_INFO("Application stop");
}

}  //namespace ME