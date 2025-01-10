#pragma once
#include <cstdint>
#include <sstream>
#include <vector>
#include <string>
#include "Event.h"

namespace ME
{
class WindowResizeEvent : public Event
{
public:
    WindowResizeEvent(uint32_t width, uint32_t height)
        : m_Width(width)
        , m_Height(height)
    {
    }

public:
    uint32_t GetWidth() { return m_Width; }

    uint32_t GetHeight() { return m_Height; }

    static EventType GetStaticType() { return EventType::WindowResize; }

    virtual EventType GetEventType() const override { return GetStaticType(); }

    virtual const char* GetName() const override { return "WindowResize"; }

    virtual int GetCategoryFlags() const override { return EventCategoryApplication; }

    virtual std::string ToString() const override
    {
        std::stringstream ss;
        ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
        return ss.str();
    }

private:
    uint32_t m_Width = 0;
    uint32_t m_Height = 0;
};

class WindowCloseEvent : public Event
{
public:
    WindowCloseEvent() = default;

public:
    static EventType GetStaticType() { return EventType::WindowClose; }

    virtual EventType GetEventType() const override { return GetStaticType(); }

    virtual const char* GetName() const override { return "WindowClose"; }

    virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
};

class FileDropEvent : public Event
{
public:
    FileDropEvent(const std::vector<std::string> dropFiles)
        : m_DropFiles(dropFiles)
    {
    }

public:
    const std::vector<std::string> GetDropFiles() const { return m_DropFiles; }

    static EventType GetStaticType() { return EventType::FileDrop; }

    virtual EventType GetEventType() const override { return GetStaticType(); }

    virtual const char* GetName() const override { return "FileDrop"; }

    virtual int GetCategoryFlags() const override { return EventCategoryApplication; }

private:
    std::vector<std::string> m_DropFiles;
};

class AppTickEvent : public Event
{
public:
    AppTickEvent() = default;

public:
    static EventType GetStaticType() { return EventType::AppTick; }

    virtual EventType GetEventType() const override { return GetStaticType(); }

    virtual const char* GetName() const override { return "AppTick"; }

    virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
};

class AppUpdateEvent : public Event
{
public:
    AppUpdateEvent() = default;

public:
    static EventType GetStaticType() { return EventType::AppUpdate; }

    virtual EventType GetEventType() const override { return GetStaticType(); }

    virtual const char* GetName() const override { return "AppUpdate"; }

    virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
};

class AppRenderEvent : public Event
{
public:
    AppRenderEvent() = default;

public:
    static EventType GetStaticType() { return EventType::AppRender; }

    virtual EventType GetEventType() const override { return GetStaticType(); }

    virtual const char* GetName() const override { return "AppRender"; }

    virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
};
}  //namespace ME