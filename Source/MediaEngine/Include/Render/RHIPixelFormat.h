#pragma once
#include <cstdint>

namespace ME
{
enum class ERHIPixelFormat : uint32_t
{
    PF_Unknown = 0,
    PF_R8,
    PF_R8G8,
    PF_R8G8B8,
    PF_R8G8B8A8,
};

}  //namespace ME