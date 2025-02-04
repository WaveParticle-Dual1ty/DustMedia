#include "MediaEngine/Include/Media/ImageDetect.h"

extern "C" {
#include "libavutil/avutil.h"
#include "libavformat/avformat.h"
}

namespace ME
{
class ImageDetectImpl : public ImageDetect
{
public:
    ImageDetectImpl(const std::string& path);

public:
    virtual void Detect() override;
    virtual bool Avaliable() override;
    virtual ImageInfo GetImageInfo() override;
    virtual const ImageInfo& GetImageInfo() const override;

private:
    bool IsImageType(AVCodecID id);

private:
    bool m_IsAvaliable = false;
    ImageInfo m_ImageInfo;
};

}  //namespace ME