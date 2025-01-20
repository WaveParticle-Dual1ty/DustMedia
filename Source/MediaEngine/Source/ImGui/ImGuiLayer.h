#pragma once
#include <string>
#include "MediaEngine/Include/Core/Ptr.h"
#include "MediaEngine/Include/Application/Layer.h"
#include "MediaEngine/Include/Render/RHI.h"

namespace ME
{
class ImGuiLayer : public Layer
{
public:
    ImGuiLayer(const std::string& name);
    virtual ~ImGuiLayer() = default;
    static Ref<ImGuiLayer> Create(RHI::API api);

public:
    virtual void Begin() = 0;
    virtual void End() = 0;
};

}  //namespace ME