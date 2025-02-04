#include "MediaEngine/Include/FileSystem/FileReader.h"

namespace ME
{
FileReader::FileReader(const std::string& path)
    : m_PathInString(path)
{
    m_FSPath = std::filesystem::path(path);
}

void FileReader::Detect()
{
    if (!std::filesystem::is_regular_file(m_FSPath))
        return;

    if (!std::filesystem::exists(m_FSPath))
        return;

    m_IsExist = true;
    m_FileName = m_FSPath.filename().string();
    m_FullPath = m_FSPath.string();
    m_FileSizeInByte = std::filesystem::file_size(m_FSPath);
    m_FileSizeInStr = ConvertFileSizeToStr(m_FileSizeInByte);
}

bool FileReader::IsExist() const
{
    return m_IsExist;
}

std::string FileReader::GetFileName()
{
    return m_FileName;
}

const std::string& FileReader::GetFileName() const
{
    return m_FileName;
}

std::string FileReader::GetFullPath()
{
    return m_FullPath;
}

const std::string& FileReader::GetFullPath() const
{
    return m_FullPath;
}

uintmax_t FileReader::GetFileSizeInByte() const
{
    return m_FileSizeInByte;
}

std::string FileReader::GetFileSizeInStr()
{
    return m_FileSizeInStr;
}

const std::string& FileReader::GetFileSizeInStr() const
{
    return m_FileSizeInStr;
}

std::string FileReader::ConvertFileSizeToStr(uintmax_t filesize)
{
    std::string res;

    if (filesize < 1024 * 1024)
    {
        std::string sizeInByte = std::to_string(filesize);
        std::string sizeInKB = std::to_string(filesize / 1024.f);
        res = sizeInKB + "KB (" + sizeInByte + ")";
    }
    else if (filesize < 1024 * 1024 * 1024)
    {
        std::string sizeInByte = std::to_string(filesize);
        std::string sizeInMB = std::to_string(filesize / 1024.f / 1024.f);
        res = sizeInMB + "MB (" + sizeInByte + ")";
    }
    else
    {
        std::string sizeInByte = std::to_string(filesize);
        std::string sizeInTB = std::to_string(filesize / 1024.f / 1024.f / 1024.f);
        res = sizeInTB + "TB (" + sizeInByte + ")";
    }

    return res;
}

}  //namespace ME