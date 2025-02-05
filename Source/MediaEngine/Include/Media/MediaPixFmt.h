#pragma once
#include <cstdint>

namespace ME
{
enum class EMPixelFormat : uint32_t
{
    None = 0,
    BGR24,
    BGRA32,
    YUVJ420P,
};

}  //namespace ME