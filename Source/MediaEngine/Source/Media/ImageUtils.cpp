#include "MediaEngine/Include/Media/ImageDetect.h"
#include "MediaEngine/Include/Core/Assert.h"
#include "ImageUtils.h"

namespace ME
{
namespace Utils
{
EImageType ConvertAVCodecIDToEImageType(AVCodecID id)
{
    EImageType res = EImageType::Undefined;

    switch (id)
    {
        case AV_CODEC_ID_MJPEG:
            res = EImageType::MJPEG;
            break;
        default:
            res = EImageType::Undefined;
            ME_ASSERT(false, "ConvertAVCodecIDToEImageType: Not support AVCodecID now");
            break;
    }

    return res;
}

EMPixelFormat ConvertAVPixelFormatToEMPixelFormat(AVPixelFormat format)
{
    EMPixelFormat res = EMPixelFormat::None;

    switch (format)
    {
        case AV_PIX_FMT_YUVJ420P:
            res = EMPixelFormat::YUVJ420P;
            break;
        default:
            res = EMPixelFormat::None;
            ME_ASSERT(false, "ConvertAVPixelFormatToEMPixelFormat: Not support AVPixelFormat now");
            break;
    }

    return res;
}
}  //namespace Utils

}  //namespace ME