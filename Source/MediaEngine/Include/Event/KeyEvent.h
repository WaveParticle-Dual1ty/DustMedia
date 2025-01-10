#pragma once
#include <cstdint>
#include <sstream>
#include "KeyCodes.h"
#include "Event.h"

namespace ME
{
class KeyEvent : public Event
{
public:
    KeyCode GetKeyCode() const { return m_KeyCode; }

public:
    virtual int GetCategoryFlags() const override { return EventCategoryKeyboard | EventCategoryInput; }

protected:
    KeyEvent(KeyCode keycode)
        : m_KeyCode(keycode)
    {
    }

protected:
    KeyCode m_KeyCode;
};

class KeyPressedEvent : public KeyEvent
{
public:
    KeyPressedEvent(KeyCode keycode, bool isRepeat)
        : KeyEvent(keycode)
        , m_IsRepeat(isRepeat)
    {
    }

public:
    static EventType GetStaticType() { return EventType::KeyPressed; }

    virtual EventType GetEventType() const override { return GetStaticType(); }

    virtual const char* GetName() const override { return "KeyPressed"; }

    virtual std::string ToString() const override
    {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << static_cast<uint32_t>(m_KeyCode) << " (repeat = " << m_IsRepeat << ")";
        return ss.str();
    }

    bool IsRepeat() const { return m_IsRepeat; }

private:
    bool m_IsRepeat = false;
};

class KeyReleasedEvent : public KeyEvent
{
public:
    KeyReleasedEvent(KeyCode keycode)
        : KeyEvent(keycode)
    {
    }

public:
    static EventType GetStaticType() { return EventType::KeyReleased; }

    virtual EventType GetEventType() const override { return GetStaticType(); }

    virtual const char* GetName() const override { return "KeyReleased"; }

    virtual std::string ToString() const override
    {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << static_cast<uint32_t>(m_KeyCode);
        return ss.str();
    }
};

class KeyTypedEvent : public Event
{
public:
    KeyTypedEvent(unsigned int code)
        : m_Char(code)
    {
    }

public:
    static EventType GetStaticType() { return EventType::KeyTyped; }

    virtual EventType GetEventType() const override { return GetStaticType(); }

    virtual const char* GetName() const override { return "KeyTyped"; }

    virtual int GetCategoryFlags() const override { return EventCategoryKeyboard | EventCategoryInput; }

    virtual std::string ToString() const override
    {
        std::stringstream ss;
        ss << "KeyTypedEvent: " << char(m_Char);
        return ss.str();
    }

private:
    unsigned int m_Char = 0;
};
}  //namespace ME