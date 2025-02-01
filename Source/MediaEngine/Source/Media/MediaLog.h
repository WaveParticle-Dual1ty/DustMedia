#pragma once
#include "MediaEngine/Include/Core/Logging.h"

#define MEDIA_LOG_TRACE(fmt, ...) ME_LOG_TRACE("Media", fmt, ##__VA_ARGS__)
#define MEDIA_LOG_DEBUG(fmt, ...) ME_LOG_DEBUG("Media", fmt, ##__VA_ARGS__)
#define MEDIA_LOG_INFO(fmt, ...) ME_LOG_INFO("Media", fmt, ##__VA_ARGS__)
#define MEDIA_LOG_WARN(fmt, ...) ME_LOG_WARN("Media", fmt, ##__VA_ARGS__)
#define MEDIA_LOG_ERROR(fmt, ...) ME_LOG_ERROR("Media", fmt, ##__VA_ARGS__)
