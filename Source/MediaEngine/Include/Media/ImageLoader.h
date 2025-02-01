#pragma once
#include <cstdint>
#include <string>

namespace ME
{
class ImageLoader
{
public:
    bool Load(const std::string& imagePath);
    void Free();

    const std::string& GetFilePath();
    uint32_t GetWidth();
    uint32_t GetHeight();
    uint32_t GetDataSize();
    void* GetData();

private:
    std::string m_FilePath;
    uint32_t m_Width = 0;
    uint32_t m_Height = 0;
    uint32_t m_DataSize = 0;
    void* m_Data = nullptr;
};

}  //namespace ME