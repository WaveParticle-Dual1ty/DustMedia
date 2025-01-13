#pragma once
#include "MediaEngine/Include/Core/Logging.h"

#define RENDER_LOG_TRACE(fmt, ...) ME_LOG_TRACE("Render", fmt, ##__VA_ARGS__)
#define RENDER_LOG_DEBUG(fmt, ...) ME_LOG_DEBUG("Render", fmt, ##__VA_ARGS__)
#define RENDER_LOG_INFO(fmt, ...) ME_LOG_INFO("Render", fmt, ##__VA_ARGS__)
#define RENDER_LOG_WARN(fmt, ...) ME_LOG_WARN("Render", fmt, ##__VA_ARGS__)
#define RENDER_LOG_ERROR(fmt, ...) ME_LOG_ERROR("Render", fmt, ##__VA_ARGS__)
