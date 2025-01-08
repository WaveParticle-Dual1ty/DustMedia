#pragma once
#include <string>
#include <format>

namespace ME
{
enum class LogLevel
{
    Trace,
    Debug,
    Info,
    Warn,
    Error,
};

class Logging
{
public:
    static Logging& GetInstance();

public:
    void Write(LogLevel _level, const char* _str);

private:
    Logging();
    ~Logging();

private:
    void* m_Impl = nullptr;
};

template <typename... Args>
inline void WriteLog(LogLevel _level, const char* tag, const char* _fmt, Args&&... _args)
{
    std::string buf;
    std::vformat_to(std::back_inserter(buf), "[{}] ", std::make_format_args(tag));
    std::vformat_to(std::back_inserter(buf), _fmt, std::make_format_args(_args...));

    auto& logger = Logging::GetInstance();
    logger.Write(_level, buf.c_str());
}

template <typename... Args>
inline void WriteLog(LogLevel _level, const char* tag, const char* _fmt, const char* _file, int _line, Args&&... _args)
{
    std::string buf;
    std::vformat_to(std::back_inserter(buf), "[{}] ", std::make_format_args(tag));
    std::vformat_to(std::back_inserter(buf), _fmt, std::make_format_args(_args...));
    std::vformat_to(std::back_inserter(buf), "\n[file: {}, line: {}]", std::make_format_args(_file, _line));

    auto& logger = Logging::GetInstance();
    logger.Write(_level, buf.c_str());
}

}  //namespace ME

#define ME_LOG_TRACE(tag, fmt, ...) ME::WriteLog(ME::LogLevel::Trace, tag, fmt, ##__VA_ARGS__)
#define ME_LOG_DEBUG(tag, fmt, ...) ME::WriteLog(ME::LogLevel::Debug, tag, fmt, ##__VA_ARGS__)
#define ME_LOG_INFO(tag, fmt, ...) ME::WriteLog(ME::LogLevel::Info, tag, fmt, ##__VA_ARGS__)
#define ME_LOG_WARN(tag, fmt, ...) ME::WriteLog(ME::LogLevel::Warn, tag, fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#define ME_LOG_ERROR(tag, fmt, ...) ME::WriteLog(ME::LogLevel::Error, tag, fmt, __FILE__, __LINE__, ##__VA_ARGS__)
