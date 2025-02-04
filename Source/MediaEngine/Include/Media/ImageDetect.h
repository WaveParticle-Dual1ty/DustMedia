#pragma once
#include <cstdint>
#include <string>
#include "MediaEngine/Include/Core/Ptr.h"
#include "ImageStruct.h"

namespace ME
{
class ImageDetect
{
public:
    static Ref<ImageDetect> CreateInstance(const std::string& path);

public:
    virtual void Detect() = 0;
    virtual bool Avaliable() = 0;
    virtual ImageInfo GetImageInfo() = 0;
    virtual const ImageInfo& GetImageInfo() const = 0;
};

}  //namespace ME