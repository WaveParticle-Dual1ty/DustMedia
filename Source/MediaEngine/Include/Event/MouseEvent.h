#pragma once
#include <cstdint>
#include <sstream>
#include "Event.h"
#include "KeyCodes.h"
#include "MouseCodes.h"

namespace ME
{
class MouseMovedEvent : public Event
{
public:
    MouseMovedEvent(float x, float y)
        : m_MouseX(x)
        , m_MouseY(y)
    {
    }

public:
    float GetX() const { return m_MouseX; }

    float GetY() const { return m_MouseY; }

    static EventType GetStaticType() { return EventType::MouseMoved; }

    virtual EventType GetEventType() const override { return GetStaticType(); }

    virtual const char* GetName() const override { return "MouseMoved"; }

    virtual int GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }

    virtual std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
        return ss.str();
    }

private:
    float m_MouseX = 0;
    float m_MouseY = 0;
};

class MouseScrolledEvent : public Event
{
public:
    MouseScrolledEvent(float x, float y)
        : m_XOffset(x)
        , m_YOffset(y)
    {
    }

public:
    float GetXOffset() const { return m_XOffset; }

    float GetYOffset() const { return m_YOffset; }

    static EventType GetStaticType() { return EventType::MouseScrolled; }

    virtual EventType GetEventType() const override { return GetStaticType(); }

    virtual const char* GetName() const override { return "MouseScrolled"; }

    virtual int GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }

    virtual std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
        return ss.str();
    }

private:
    float m_XOffset = 0;
    float m_YOffset = 0;
};

class MouseButtonEvent : public Event
{
public:
    MouseCode GetMouseButton() const { return m_Button; }

public:
    virtual int GetCategoryFlags() const override
    {
        return EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton;
    }

protected:
    MouseButtonEvent(MouseCode button)
        : m_Button(button)
    {
    }

protected:
    MouseCode m_Button;
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
public:
    MouseButtonPressedEvent(MouseCode button)
        : MouseButtonEvent(button)
    {
    }

public:
    static EventType GetStaticType() { return EventType::MouseButtonPressed; }

    virtual EventType GetEventType() const override { return GetStaticType(); }

    virtual const char* GetName() const override { return "MouseButtonPressed"; }

    virtual std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: " << static_cast<int>(m_Button);
        return ss.str();
    }
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
    MouseButtonReleasedEvent(MouseCode button)
        : MouseButtonEvent(button)
    {
    }

public:
    static EventType GetStaticType() { return EventType::MouseButtonReleased; }

    virtual EventType GetEventType() const override { return GetStaticType(); }

    virtual const char* GetName() const override { return "MouseButtonPressed"; }

    virtual std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: " << static_cast<int>(m_Button);
        return ss.str();
    }
};

}  //namespace ME