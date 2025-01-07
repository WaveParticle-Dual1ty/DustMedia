#include "MediaEngine/Include/Core/Logging.h"
#include "LoggingImpl.h"

namespace MediaEngine
{
Logging& Logging::GetInstance()
{
    static Logging s_instance;
    if (s_instance.m_Impl == nullptr)
    {
        s_instance.m_Impl = new LogginImpl;
        LogginImpl* log = static_cast<LogginImpl*>(s_instance.m_Impl);
        log->Init();
    }

    return s_instance;
}

void Logging::Write(LogLevel _level, const char* _str)
{
    if (m_Impl)
    {
        LogginImpl* log = static_cast<LogginImpl*>(m_Impl);
        log->Write(_level, _str);
    }
}

Logging::Logging()
{
}

Logging::~Logging()
{
    if (m_Impl)
    {
        LogginImpl* log = static_cast<LogginImpl*>(m_Impl);
        delete log;
        m_Impl = nullptr;
    }
}

}  // namespace MediaEngine
