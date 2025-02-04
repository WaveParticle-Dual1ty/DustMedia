#pragma once
#include "MediaEngine/Include/Core/Ptr.h"
#include "MediaEngine/Include/Application/Layer.h"
#include "MediaEngine/Include/Event/ApplicationEvent.h"
#include "MediaEngine/Include/FileSystem/FileReader.h"
#include "MediaEngine/Include/Media/ImageLoader.h"
#include "MediaEngine/Include/Media/ImageDetect.h"

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
    struct Image
    {
        bool Avaliable = false;
        ME::Ref<ME::FileReader> FileReader;
        ME::Ref<ME::ImageDetect> Detect;
        ME::Ref<ME::ImageLoader> Loader;
    };

    Image m_CurrentImage;
};