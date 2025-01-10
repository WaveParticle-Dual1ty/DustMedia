#pragma once
#include <string>
#include <memory>
#include <functional>
#include "MediaEngine/Include/Event/Event.h"

namespace ME
{
struct WindowProps
{
    std::string Title = "MediaEngine";
    uint32_t Width = 1000;
    uint32_t Height = 800;
};

class Window
{
public:
    using EventCallbackFn = std::function<void(Event&)>;

public:
    virtual ~Window() = default;
    static std::shared_ptr<Window> Create();

public:
    virtual bool InitWindow(const WindowProps& props) = 0;
    virtual void Destroy() = 0;
    virtual void PollEvents() = 0;
    virtual uint32_t GetWidth() const = 0;
    virtual uint32_t GetHeight() const = 0;
    virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
    virtual void* GetNativeWindow() const = 0;
};

}  //namespace ME