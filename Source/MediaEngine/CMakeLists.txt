set(TARGET_NAME MediaEngine)

include(${PROJ_DIR}/CMake/DependVulkan.cmake)
include(${PROJ_DIR}/CMake/DependFFmpeg.cmake)

file(GLOB_RECURSE SRC_FILES "./*.h" "./*.cpp")
add_library(${TARGET_NAME} STATIC ${SRC_FILES})

target_link_libraries(${TARGET_NAME} PRIVATE
    $<$<CONFIG:Debug>:${VULKAN_LIBS_DEBUG}>
    $<$<CONFIG:Release>:${VULKAN_LIBS_RELEASE}>
    ${FFMPEG_LIBS}
    Third_spdlog
    Third_glfw
    Third_imgui
    Third_stb
)

target_include_directories(${TARGET_NAME} PRIVATE
    ${VULKAN_INCLUDE_DIR}
    ${FFMPEG_INCLUDE_DIR}
)

set_target_properties(${TARGET_NAME} PROPERTIES FOLDER Source)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC_FILES})
