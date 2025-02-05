#pragma once
#include <cstdint>
#include <string>
#include <array>
#include "MediaPixFmt.h"

namespace ME
{
enum class EImageType : uint32_t
{
    Undefined = 0,
    MJPEG,
    BMP,
};

struct ImageInfo
{
    std::string Url;
    EImageType Type = EImageType::Undefined;
    std::string TypeInStr;
    uint32_t Width = 0;
    uint32_t Height = 0;
    EMPixelFormat Format = EMPixelFormat::None;
};

struct ImageFrame
{
    uint32_t Width = 0;
    uint32_t Height = 0;
    std::array<void*, 4> Data = {nullptr, nullptr, nullptr, nullptr};
    std::array<uint32_t, 4> Linesize = {0, 0, 0, 0};
    std::array<uint32_t, 4> Datasize = {0, 0, 0, 0};
};

}  //namespace ME