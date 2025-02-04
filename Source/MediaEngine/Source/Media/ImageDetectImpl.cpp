#include "ImageDetectImpl.h"
#include <set>
#include "MediaLog.h"
#include "ImageUtils.h"

namespace ME
{
Ref<ImageDetect> ImageDetect::CreateInstance(const std::string& path)
{
    auto res = CreateRef<ImageDetectImpl>(path);
    return res;
}

ImageDetectImpl::ImageDetectImpl(const std::string& path)
{
    m_ImageInfo.Url = path;
}

void ImageDetectImpl::Detect()
{
    AVFormatContext* formatContext = nullptr;
    int ret = avformat_open_input(&formatContext, m_ImageInfo.Url.c_str(), NULL, NULL);
    if (ret < 0)
    {
        MEDIA_LOG_ERROR("avformat_open_input fail, file name: {}", m_ImageInfo.Url);
        return;
    }

    ret = avformat_find_stream_info(formatContext, NULL);
    if (ret < 0)
    {
        MEDIA_LOG_ERROR("avformat_find_stream_info fail");
        avformat_close_input(&formatContext);
        return;
    }

    AVCodecParameters* codecPara = nullptr;
    AVStream* videoStream = nullptr;
    for (unsigned int i = 0; i < formatContext->nb_streams; ++i)
    {
        AVStream* stream = formatContext->streams[i];
        if (stream->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            videoStream = stream;
            codecPara = stream->codecpar;
            break;
        }
    }

    if (!videoStream)
    {
        MEDIA_LOG_ERROR("no videoStream");
        avformat_close_input(&formatContext);
        return;
    }

    const AVCodec* codec = avcodec_find_decoder(codecPara->codec_id);
    if (!codec)
    {
        MEDIA_LOG_ERROR("avcodec_find_decoder fail");
        avformat_close_input(&formatContext);
        return;
    }

    if (!IsImageType(codecPara->codec_id))
    {
        MEDIA_LOG_WARN("Not support image file");
        return;
    }

    m_IsAvaliable = true;

    m_ImageInfo.Type = Utils::ConvertAVCodecIDToEImageType(codecPara->codec_id);
    m_ImageInfo.TypeInStr = codec->long_name;
    m_ImageInfo.Width = codecPara->width;
    m_ImageInfo.Height = codecPara->height;
    AVPixelFormat format = static_cast<AVPixelFormat>(codecPara->format);
    m_ImageInfo.Format = Utils::ConvertAVPixelFormatToEMPixelFormat(format);
}

bool ImageDetectImpl::Avaliable()
{
    return m_IsAvaliable;
}

ImageInfo ImageDetectImpl::GetImageInfo()
{
    return m_ImageInfo;
}

const ImageInfo& ImageDetectImpl::GetImageInfo() const
{
    return m_ImageInfo;
}

bool ImageDetectImpl::IsImageType(AVCodecID id)
{
    static std::set<AVCodecID> imageIDs = {
        AV_CODEC_ID_MJPEG,
    };

    if (imageIDs.find(id) != imageIDs.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}
}  //namespace ME