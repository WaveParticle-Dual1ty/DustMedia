#pragma once
#include <cassert>
#include "Logging.h"

#define ME_ASSERT(condition, log)                       \
    if (!(condition))                                   \
    {                                                   \
        ME_LOG_ERROR("Assert", "Assert fail: {}", log); \
        assert(false);                                  \
    }
