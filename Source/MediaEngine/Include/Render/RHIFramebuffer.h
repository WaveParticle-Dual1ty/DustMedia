#pragma once
#include <cstdint>
#include <vector>
#include "MediaEngine/Include/Core/Ptr.h"
#include "RHIPixelFormat.h"
#include "RHIResources.h"
#include "RHITexture.h"

namespace ME
{
class RHIFramebuffer
{
public:
    virtual ~RHIFramebuffer() = default;

public:
    Ref<RHITexture2D> GetTargetTexture(uint32_t index);

protected:
    uint32_t m_Width = 0;
    uint32_t m_Height = 0;
    Ref<RHIRenderPass> m_RenderPass;
    std::vector<Ref<RHITexture2D>> m_Textures;
};

}  //namespace ME