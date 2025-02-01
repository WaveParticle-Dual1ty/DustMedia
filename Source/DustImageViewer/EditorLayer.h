#pragma once
#include "MediaEngine/Include/Application/Layer.h"

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
};