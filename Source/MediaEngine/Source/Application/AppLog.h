#pragma once
#include "MediaEngine/Include/Core/Logging.h"

#define APP_LOG_TRACE(fmt, ...) ME_LOG_TRACE("Application", fmt, ##__VA_ARGS__)
#define APP_LOG_DEBUG(fmt, ...) ME_LOG_DEBUG("Application", fmt, ##__VA_ARGS__)
#define APP_LOG_INFO(fmt, ...) ME_LOG_INFO("Application", fmt, ##__VA_ARGS__)
#define APP_LOG_WARN(fmt, ...) ME_LOG_WARN("Application", fmt, ##__VA_ARGS__)
#define APP_LOG_ERROR(fmt, ...) ME_LOG_ERROR("Application", fmt, ##__VA_ARGS__)
