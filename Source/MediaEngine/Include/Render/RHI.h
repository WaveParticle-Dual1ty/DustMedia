#pragma once
#include <memory>
#include "MediaEngine/Include/Core/Ptr.h"
#include "MediaEngine/Include/Window/Window.h"
#include "RHIStruct.h"
#include "RHIResources.h"
#include "RHITexture.h"
#include "RHIFramebuffer.h"

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
    virtual Ref<RHITexture2D> GetCurrentBackTexture() = 0;

    // ImGui
    virtual void* CreateImTextureID(Ref<RHITexture2D> texture) = 0;

    // Resources
    virtual Ref<RHITexture2D> CreateRHITexture2D(RHITexture2DCreateDesc desc) = 0;
    virtual Ref<RHIRenderPass> CreateRHIRenderPass(RHIRenderPassCreateDesc desc) = 0;
    virtual Ref<RHIFramebuffer> CreateRHIFramebuffer(
        uint32_t width,
        uint32_t height,
        Ref<RHIRenderPass> renderPass,
        std::vector<Ref<RHITexture2D>>& textures) = 0;

    virtual void DestroyRHITexture2D(Ref<RHITexture2D> texture) = 0;
    virtual void DestroyRHIRenderPass(Ref<RHIRenderPass> renderPass) = 0;
    virtual void DestroyRHIFramebuffer(Ref<RHIFramebuffer> framebuffer) = 0;

    // Command
    virtual bool BeginCommandBuffer(Ref<RHICommandBuffer> cmdBuffer) = 0;
    virtual bool EndCommandBuffer(Ref<RHICommandBuffer> cmdBuffer) = 0;
    virtual void CmdPushEvent(Ref<RHICommandBuffer> cmdBuffer, const char* name, RHIColor color) = 0;
    virtual void CmdPopEvent(Ref<RHICommandBuffer> cmdBuffer) = 0;
    virtual void CmdBeginRenderPass(Ref<RHICommandBuffer> cmdBuffer, RHIRenderPassBeginInfo beginIhfo) = 0;
    virtual void CmdEndRenderPass(Ref<RHICommandBuffer> cmdBuffer) = 0;
    virtual void CmdClearColor(Ref<RHICommandBuffer> cmdBuffer, Ref<RHITexture2D> texture, RHIColor color) = 0;
    virtual void CmdPipelineBarrier(Ref<RHICommandBuffer> cmdBuffer, RHIPipelineBarrierInfo barrierInfo) = 0;
    virtual void CmdCopyTexture(Ref<RHICommandBuffer> cmdBuffer, Ref<RHITexture2D> src, Ref<RHITexture2D> dst) = 0;
};
}  //namespace ME