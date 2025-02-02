﻿#pragma once
#include "MediaEngine/Include/Core/Ptr.h"
#include "MediaEngine/Include/Application/Layer.h"
#include "MediaEngine/Include/Event/ApplicationEvent.h"
#include "MediaEngine/Include/Media/ImageLoader.h"

class EditorLayer : public ME::Layer
{
public:
    EditorLayer();

public:
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(ME::Timestep timestep) override;
    virtual void OnUIUpdate() override;
    virtual void OnEvent(ME::Event& event) override;

private:
    void BeginDockspace();
    void EndDockspace();

    bool OnFileDrop(ME::FileDropEvent& event);

private:
    ME::Ref<ME::ImageLoader> m_CurrentImage;
};