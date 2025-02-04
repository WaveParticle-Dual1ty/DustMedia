#pragma once
#include "MediaEngine/Include/Media/ImageLoader.h"

extern "C" {
#include "libavutil/avutil.h"
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
}

namespace ME
{
class ImageLoaderImpl : public ImageLoader
{
public:
    ImageLoaderImpl(const std::string& path);

public:
    virtual void Detect() override;
    virtual bool Avaliable() override;
    virtual ImageInfo GetImageInfo() override;
    virtual const ImageInfo& GetImageInfo() const override;
    virtual bool Load() override;
    virtual ImageFrame GetImageFrame() override;

private:
    bool IsImageType(AVCodecID id);

private:
    bool m_IsAvaliable = false;
    ImageInfo m_ImageInfo;

    AVFormatContext* m_FormatContext = nullptr;
    AVStream* m_Stream = nullptr;
    AVCodecParameters* m_CodecPara = nullptr;
    const AVCodec* m_Codec = nullptr;

    ImageFrame m_ImageFrame;
};

}  //namespace ME