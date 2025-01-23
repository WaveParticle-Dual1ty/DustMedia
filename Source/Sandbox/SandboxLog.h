#pragma once
#include "MediaEngine/Include/Core/Logging.h"

#define SANDBOX_LOG_TRACE(fmt, ...) ME_LOG_TRACE("Sandbox", fmt, ##__VA_ARGS__)
#define SANDBOX_LOG_DEBUG(fmt, ...) ME_LOG_DEBUG("Sandbox", fmt, ##__VA_ARGS__)
#define SANDBOX_LOG_INFO(fmt, ...) ME_LOG_INFO("Sandbox", fmt, ##__VA_ARGS__)
#define SANDBOX_LOG_WARN(fmt, ...) ME_LOG_WARN("Sandbox", fmt, ##__VA_ARGS__)
#define SANDBOX_LOG_ERROR(fmt, ...) ME_LOG_ERROR("Sandbox", fmt, ##__VA_ARGS__)
