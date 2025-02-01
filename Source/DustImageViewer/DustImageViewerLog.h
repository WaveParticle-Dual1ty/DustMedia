#pragma once
#include "MediaEngine/Include/Core/Logging.h"

#define IMAGEVIWER_LOG_TRACE(fmt, ...) ME_LOG_TRACE("ImageViewer", fmt, ##__VA_ARGS__)
#define IMAGEVIWER_LOG_DEBUG(fmt, ...) ME_LOG_DEBUG("ImageViewer", fmt, ##__VA_ARGS__)
#define IMAGEVIWER_LOG_INFO(fmt, ...) ME_LOG_INFO("ImageViewer", fmt, ##__VA_ARGS__)
#define IMAGEVIWER_LOG_WARN(fmt, ...) ME_LOG_WARN("ImageViewer", fmt, ##__VA_ARGS__)
#define IMAGEVIWER_LOG_ERROR(fmt, ...) ME_LOG_ERROR("ImageViewer", fmt, ##__VA_ARGS__)
