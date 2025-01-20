#pragma once
#include "MediaEngine/Include/Core/Logging.h"

#define IMGUI_LOG_TRACE(fmt, ...) ME_LOG_TRACE("ImGui", fmt, ##__VA_ARGS__)
#define IMGUI_LOG_DEBUG(fmt, ...) ME_LOG_DEBUG("ImGui", fmt, ##__VA_ARGS__)
#define IMGUI_LOG_INFO(fmt, ...) ME_LOG_INFO("ImGui", fmt, ##__VA_ARGS__)
#define IMGUI_LOG_WARN(fmt, ...) ME_LOG_WARN("ImGui", fmt, ##__VA_ARGS__)
#define IMGUI_LOG_ERROR(fmt, ...) ME_LOG_ERROR("ImGui", fmt, ##__VA_ARGS__)
