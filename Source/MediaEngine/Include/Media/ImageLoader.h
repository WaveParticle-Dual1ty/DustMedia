#pragma once
#include <cstdint>
#include <string>
#include "MediaEngine/Include/Core/Ptr.h"
#include "ImageStruct.h"

namespace ME
{
class ImageLoader
{
public:
    static Ref<ImageLoader> CreateInstance(const std::string& path);

public:
    virtual void Detect() = 0;
    virtual bool Avaliable() = 0;
    virtual ImageInfo GetImageInfo() = 0;
    virtual const ImageInfo& GetImageInfo() const = 0;
    virtual bool Load() = 0;
    virtual ImageFrame GetImageFrame() = 0;
};

}  //namespace ME