#pragma once
#include <cstdint>
#include <string>
#include "MediaPixFmt.h"

namespace ME
{
enum class EImageType : uint32_t
{
    Undefined = 0,
    MJPEG,
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

}  //namespace ME