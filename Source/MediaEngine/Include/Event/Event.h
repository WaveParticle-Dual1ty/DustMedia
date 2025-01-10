#pragma once
#include <string>
#include <functional>

namespace ME
{
enum class EventType
{
    None = 0,
    WindowClose,
    WindowResize,
    WindowFocus,
    WindowLostFocus,
    WindowMoved,
    FileDrop,
    AppTick,
    AppUpdate,
    AppRender,
    KeyPressed,
    KeyReleased,
    KeyTyped,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled,
};

enum EventCategory : int
{
    None = 0,
    EventCategoryApplication = (1 << 0),
    EventCategoryInput = (1 << 1),
    EventCategoryKeyboard = (1 << 2),
    EventCategoryMouse = (1 << 3),
    EventCategoryMouseButton = (1 << 4),
};

class Event
{
public:
    virtual ~Event() = default;

public:
    virtual EventType GetEventType() const = 0;
    virtual const char* GetName() const = 0;
    virtual int GetCategoryFlags() const = 0;

    virtual std::string ToString() const { return GetName(); }

    bool IsInCategory(EventCategory category) { return GetCategoryFlags() & category; }

    bool Handled = false;
};

class EventDispatcher
{
    template <typename T>
    using EventFn = std::function<bool(T&)>;

public:
    EventDispatcher(Event& event)
        : m_Event(event)
    {
    }

    template <typename T>
    bool Dispatch(EventFn<T> func)
    {
        if (m_Event.GetEventType() == T::GetStaticType())
        {
            m_Event.Handled = func(*(T*)&m_Event);
            return true;
        }
        return false;
    }

private:
    Event& m_Event;
};

}  //namespace ME