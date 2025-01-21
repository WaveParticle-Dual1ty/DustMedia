#pragma once
#include <cstdint>
#include "RHIResources.h"
#include "RHITexture.h"
#include "RHIFrameBuffer.h"

namespace ME
{
struct RHIRenderArea
{
    int32_t OffsetX = 0;
    int32_t OffsetY = 0;
    uint32_t Width = 0;
    uint32_t Height = 0;
};

struct RHIColorClearValue
{
    float R = 0;
    float G = 0;
    float B = 0;
    float A = 0;
};

struct RHIRenderPassBeginInfo
{
    RHIRenderArea RenderArea;
    RHIColorClearValue ColorClearValue;
    Ref<RHIRenderPass> RenderPass;
    Ref<RHIFramebuffer> Framebuffer;
};

}  //namespace ME