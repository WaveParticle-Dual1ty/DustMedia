set(TARGET_NAME Third_spdlog)

file(GLOB_RECURSE SPDLOG_SRC_FILES
    "${PROJ_THIRDPARTY_DIR}/spdlog/include/spdlog/*.h"
    "${PROJ_THIRDPARTY_DIR}/spdlog/src/*.cpp"
)

add_library(${TARGET_NAME} STATIC ${SPDLOG_SRC_FILES})
target_include_directories(${TARGET_NAME} PUBLIC ${PROJ_THIRDPARTY_DIR}/spdlog/include)
target_compile_definitions(${TARGET_NAME} PUBLIC SPDLOG_COMPILED_LIB)
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER Source/ThirdParty)
source_group(TREE ${PROJ_THIRDPARTY_DIR} FILES ${SPDLOG_SRC_FILES})
