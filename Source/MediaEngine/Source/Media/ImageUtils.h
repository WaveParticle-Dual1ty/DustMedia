#pragma once
#include <cstdint>

extern "C" {
#include "libavutil/avutil.h"
#include "libavformat/avformat.h"
}

#include "MediaEngine/Include/Media/ImageStruct.h"
#include "MediaEngine/Include/Media/MediaPixFmt.h"

namespace ME
{
namespace Utils
{
EImageType ConvertAVCodecIDToEImageType(AVCodecID id);
EMPixelFormat ConvertAVPixelFormatToEMPixelFormat(AVPixelFormat format);
}  //namespace Utils

}  //namespace ME