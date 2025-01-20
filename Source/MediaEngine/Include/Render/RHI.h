#pragma once
#include <memory>
#include "MediaEngine/Include/Core/Ptr.h"
#include "MediaEngine/Include/Window/Window.h"
#include "RHIResources.h"
#include "RHITexture.h"

namespace ME
{
class RHI
{
public:
    enum class API
    {
        Vulkan,
    };

public:
    virtual ~RHI() = default;
    static std::shared_ptr<RHI> CreateRHI(API api);

public:
    virtual bool Initialize(std::shared_ptr<Window> wnd) = 0;
    virtual bool Resize(uint32_t width, uint32_t height) = 0;
    virtual bool PrepareForNextFrame() = 0;
    virtual bool SubmmitRenderCommands() = 0;
    virtual bool Present() = 0;

    virtual Ref<RHICommandBuffer> GetCurrentCommandBuffer() const = 0;

    virtual Ref<RHITexture2D> CreateTexture2D(RHITexture2DCreateDesc desc) = 0;

    virtual bool BeginCommandBuffer(Ref<RHICommandBuffer> commandBuffer) = 0;
    virtual bool EndCommandBuffer(Ref<RHICommandBuffer> commandBuffer) = 0;

    // test interface
    virtual bool ClearBackBuffer(Ref<RHICommandBuffer> commandBuffer, float r, float g, float b, float a) = 0;
};
}  //namespace ME