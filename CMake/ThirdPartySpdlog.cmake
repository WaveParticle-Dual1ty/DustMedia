set(TARGET_SPDLOG Third_spdlog)

file(GLOB_RECURSE SPDLOG_SRC_FILES
    "${PROJ_THIRDPARTY_DIR}/spdlog/include/spdlog/*.h"
    "${PROJ_THIRDPARTY_DIR}/spdlog/src/*.cpp"
)

add_library(${TARGET_SPDLOG} STATIC ${SPDLOG_SRC_FILES})
target_include_directories(${TARGET_SPDLOG} PUBLIC ${PROJ_THIRDPARTY_DIR}/spdlog/include)
target_compile_definitions(${TARGET_SPDLOG} PUBLIC SPDLOG_COMPILED_LIB)
set_target_properties(${TARGET_SPDLOG} PROPERTIES FOLDER Source/ThirdParty)
source_group(TREE ${PROJ_THIRDPARTY_DIR} FILES ${SPDLOG_SRC_FILES})
