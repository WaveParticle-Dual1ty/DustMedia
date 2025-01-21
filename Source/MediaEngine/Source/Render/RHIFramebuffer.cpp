#include "MediaEngine/Include/Render/RHIFramebuffer.h"
#include "MediaEngine/Include/Core/Assert.h"

namespace ME
{
Ref<RHITexture2D> RHIFramebuffer::GetTargetTexture(uint32_t index)
{
    ME_ASSERT(index < m_Textures.size(), "Index out of range")

    return m_Textures[index];
}
}  //namespace ME