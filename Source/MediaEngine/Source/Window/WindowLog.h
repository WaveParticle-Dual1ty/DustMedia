#pragma once
#include "MediaEngine/Include/Core/Logging.h"

#define WND_LOG_TRACE(fmt, ...) ME_LOG_TRACE("Window", fmt, ##__VA_ARGS__)
#define WND_LOG_DEBUG(fmt, ...) ME_LOG_DEBUG("Window", fmt, ##__VA_ARGS__)
#define WND_LOG_INFO(fmt, ...) ME_LOG_INFO("Window", fmt, ##__VA_ARGS__)
#define WND_LOG_WARN(fmt, ...) ME_LOG_WARN("Window", fmt, ##__VA_ARGS__)
#define WND_LOG_ERROR(fmt, ...) ME_LOG_ERROR("Window", fmt, ##__VA_ARGS__)