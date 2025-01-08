#pragma once
#include <memory>

namespace ME
{
class Application
{
public:
    virtual ~Application() = default;

public:
    void Run();

private:
    bool m_Running = true;
};

std::unique_ptr<Application> CreateApplication();

}  //namespace ME