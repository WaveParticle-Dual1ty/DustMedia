#include "MediaEngine/Include/Render/RHITexture.h"

namespace ME
{
uint32_t RHITexture2D::GetWidth() const
{
    return m_Width;
}

uint32_t RHITexture2D::GetHeight() const
{
    return m_Height;
}
}  //namespace ME