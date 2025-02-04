#pragma once
#include <filesystem>
#include <string>

namespace ME
{
class FileReader
{
public:
    FileReader(const std::string& path);

public:
    void Detect();
    bool IsExist() const;
    std::string GetFileName();
    const std::string& GetFileName() const;
    std::string GetFullPath();
    const std::string& GetFullPath() const;
    uintmax_t GetFileSizeInByte() const;
    std::string GetFileSizeInStr();
    const std::string& GetFileSizeInStr() const;

private:
    std::string ConvertFileSizeToStr(uintmax_t filesize);

private:
    std::string m_PathInString;
    std::filesystem::path m_FSPath;

    bool m_IsExist = false;
    std::string m_FileName;
    std::string m_FullPath;
    uintmax_t m_FileSizeInByte = 0;
    std::string m_FileSizeInStr;
};

}  //namespace ME