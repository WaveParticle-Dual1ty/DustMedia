#include "MediaEngine/Include/Media/ImageLoader.h"
#include "ThirdParty/stb/stb_image.h"
#include "MediaLog.h"

namespace ME
{
bool ImageLoader::Load(const std::string& imagePath)
{
    m_FilePath = imagePath;

    int width = 0;
    int height = 0;
    int channels = 0;
    unsigned char* data = stbi_load(imagePath.c_str(), &width, &height, &channels, 0);
    if (data == nullptr)
    {
        MEDIA_LOG_ERROR("stbi_load load fail: {}", imagePath);
        return false;
    }

    m_Width = width;
    m_Height = height;
    m_Data = data;
    m_DataSize = width * height * channels;

    return true;
}

void ImageLoader::Free()
{
    stbi_image_free(m_Data);
}

const std::string& ImageLoader::GetFilePath()
{
    return m_FilePath;
}

uint32_t ImageLoader::GetWidth()
{
    return m_Width;
}

uint32_t ImageLoader::GetHeight()
{
    return m_Height;
}

uint32_t ImageLoader::GetDataSize()
{
    return m_DataSize;
}

void* ImageLoader::GetData()
{
    return m_Data;
}
}  //namespace ME