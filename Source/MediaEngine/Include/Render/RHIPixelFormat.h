#pragma once
#include <cstdint>

namespace ME
{
enum class ERHIPixelFormat : uint32_t
{
    PF_Unknown = 0,
    PF_R8_UNORM,
    PF_R8G8_UNORM,
    PF_R8G8B8_UNORM,
    PF_R8G8B8A8_UNORM,
    PF_B8G8R8_UNORM,
    PF_B8G8R8A8_UNORM,
};

}  //namespace ME
