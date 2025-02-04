#pragma once
#include <cstdint>

namespace ME
{
enum class EMPixelFormat : uint32_t
{
    None = 0,
    BGR24,
    YUVJ420P,
};

}  //namespace ME