#include "LoggingImpl.h"

namespace ME
{
void LogginImpl::Init()
{
    const std::string patt = "[%Y-%m-%d %H:%M:%S.%e] [%l] [thread %t] %v%$";

    m_StdoutSink = std::make_shared<spdlog::sinks::stdout_color_sink_st>();
    m_StdoutSink->set_level(spdlog::level::trace);
    m_StdoutSink->set_pattern(patt);

    m_FileSink = std::make_shared<spdlog::sinks::basic_file_sink_st>("Log/Log.txt", true);
    m_FileSink->set_level(spdlog::level::trace);
    m_FileSink->set_pattern(patt);

    m_Logger = std::shared_ptr<spdlog::logger>(new spdlog::logger("Log", {m_StdoutSink, m_FileSink}));
    m_Logger->set_level(spdlog::level::trace);
}

void LogginImpl::Write(LogLevel _level, const char* _str)
{
    switch (_level)
    {
        case LogLevel::Trace:
            m_Logger->trace(_str);
            break;
        case LogLevel::Debug:
            m_Logger->debug(_str);
            break;
        case LogLevel::Info:
            m_Logger->info(_str);
            break;
        case LogLevel::Warn:
            m_Logger->warn(_str);
            break;
        case LogLevel::Error:
            m_Logger->error(_str);
            break;
        default:
            break;
    }
}

}  //namespace ME