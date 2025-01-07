#pragma once
#include <memory>

#pragma warning(push)
#pragma warning(disable : 4996)
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#pragma warning(pop)

#include "MediaEngine/Include/Core/Logging.h"

namespace MediaEngine
{
class LogginImpl
{
public:
    void Init();
    void Write(LogLevel _level, const char* _str);

private:
    std::shared_ptr<spdlog::sinks::stdout_color_sink_st> m_StdoutSink;
    std::shared_ptr<spdlog::sinks::basic_file_sink_st> m_FileSink;
    std::shared_ptr<spdlog::logger> m_Logger;
};

}  // namespace MediaEngine