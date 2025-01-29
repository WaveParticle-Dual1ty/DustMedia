#include "MediaEngine/Include/Application/EntryPoint.h"
#include "MediaEngine/Include/Application/Application.h"
#include "AppLog.h"

int main(int argc, char** argv)
{
    static_cast<void>(argc);
    static_cast<void>(argv);

    APP_LOG_INFO("Start EntryPoint");

    auto app = ME::CreateApplication();
    app->Run();

    APP_LOG_INFO("Process stop");
    return 1;
}
