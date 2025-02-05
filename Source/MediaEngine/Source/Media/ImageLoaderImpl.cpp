#include "ImageLoaderImpl.h"
#include <set>
#include "MediaLog.h"
#include "ImageUtils.h"

namespace ME
{
Ref<ImageLoader> ImageLoader::CreateInstance(const std::string& path)
{
    auto res = CreateRef<ImageLoaderImpl>(path);
    return res;
}

ImageLoaderImpl::ImageLoaderImpl(const std::string& path)
{
    m_ImageInfo.Url = path;
}

void ImageLoaderImpl::Detect()
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

    m_FormatContext = formatContext;
    m_Stream = videoStream;
    m_CodecPara = codecPara;
    m_Codec = codec;
}

bool ImageLoaderImpl::Avaliable()
{
    return m_IsAvaliable;
}

ImageInfo ImageLoaderImpl::GetImageInfo()
{
    return m_ImageInfo;
}

const ImageInfo& ImageLoaderImpl::GetImageInfo() const
{
    return m_ImageInfo;
}

bool ImageLoaderImpl::Load()
{
    AVCodecContext* codecContext = avcodec_alloc_context3(m_Codec);
    if (!codecContext)
    {
        MEDIA_LOG_ERROR("avcodec_alloc_context3 fail");
        return false;
    }

    int ret = avcodec_parameters_to_context(codecContext, m_CodecPara);
    if (ret < 0)
    {
        MEDIA_LOG_ERROR("avcodec_parameters_to_context fail");
        return false;
    }

    ret = avcodec_open2(codecContext, m_Codec, NULL);
    if (ret < 0)
    {
        MEDIA_LOG_ERROR("avcodec_open2 fail");
        return false;
    }

    AVFrame* frame = av_frame_alloc();

    AVPacket packet;
    av_init_packet(&packet);
    ret = av_read_frame(m_FormatContext, &packet);
    if (ret < 0)
    {
        MEDIA_LOG_ERROR("av_read_frame fail");
        return false;
    }

    if (packet.stream_index != m_Stream->index)
    {
        MEDIA_LOG_ERROR("AVPacket/AVStream index not match");
        return false;
    }

    ret = avcodec_send_packet(codecContext, &packet);
    if (ret < 0)
    {
        MEDIA_LOG_ERROR("avcodec_send_packet fail");
        return false;
    }

    ret = avcodec_receive_frame(codecContext, frame);
    if (ret < 0)
    {
        MEDIA_LOG_ERROR("avcodec_receive_frame fail");
        return false;
    }

    m_ImageFrame.Width = frame->width;
    m_ImageFrame.Height = frame->height;
    m_ImageFrame.Data[0] = frame->data[0];
    m_ImageFrame.Data[1] = frame->data[1];
    m_ImageFrame.Data[2] = frame->data[2];
    m_ImageFrame.Data[3] = frame->data[3];
    m_ImageFrame.Linesize[0] = static_cast<uint32_t>(frame->linesize[0]);
    m_ImageFrame.Linesize[1] = static_cast<uint32_t>(frame->linesize[1]);
    m_ImageFrame.Linesize[2] = static_cast<uint32_t>(frame->linesize[2]);
    m_ImageFrame.Linesize[3] = static_cast<uint32_t>(frame->linesize[3]);

    // todo
    m_ImageFrame.Datasize[0] = frame->linesize[0] * frame->height;
    m_ImageFrame.Datasize[1] = 0;
    m_ImageFrame.Datasize[2] = 0;
    m_ImageFrame.Datasize[3] = 0;

    return true;
}

ImageFrame ImageLoaderImpl::GetImageFrame()
{
    return m_ImageFrame;
}

bool ImageLoaderImpl::IsImageType(AVCodecID id)
{
    static std::set<AVCodecID> imageIDs = {AV_CODEC_ID_MJPEG, AV_CODEC_ID_BMP};

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