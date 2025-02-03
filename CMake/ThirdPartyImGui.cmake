set(TARGET_NAME Third_imgui)

include(${PROJ_DIR}/CMake/DependVulkan.cmake)

set(IMGUI_SRC_DIR ${PROJ_THIRDPARTY_DIR}/imgui)

set(IMGUI_COMMON_SOURCES
    ${IMGUI_SRC_DIR}/imconfig.h
    ${IMGUI_SRC_DIR}/imgui.cpp
    ${IMGUI_SRC_DIR}/imgui.h
    ${IMGUI_SRC_DIR}/imgui_demo.cpp
    ${IMGUI_SRC_DIR}/imgui_draw.cpp
    ${IMGUI_SRC_DIR}/imgui_internal.h
    ${IMGUI_SRC_DIR}/imgui_tables.cpp
    ${IMGUI_SRC_DIR}/imgui_widgets.cpp
)

if (WIN32)
    set(IMGUI_SOURCES
        ${IMGUI_COMMON_SOURCES}
        ${IMGUI_SRC_DIR}/backends/imgui_impl_glfw.h
        ${IMGUI_SRC_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_SRC_DIR}/backends/imgui_impl_vulkan.h
        ${IMGUI_SRC_DIR}/backends/imgui_impl_vulkan.cpp
    )
elseif(APPLE)
    set(IMGUI_SOURCES
        ${IMGUI_COMMON_SOURCES}
        ${IMGUI_SRC_DIR}/backends/imgui_impl_glfw.h
        ${IMGUI_SRC_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_SRC_DIR}/backends/imgui_impl_vulkan.h
        ${IMGUI_SRC_DIR}/backends/imgui_impl_vulkan.cpp
    )
else()
    message(FATAL_ERROR "Unsuport platform")
endif()

add_library(${TARGET_NAME} STATIC ${IMGUI_SOURCES})
target_include_directories(${TARGET_NAME} PUBLIC
    ${PROJ_THIRDPARTY_DIR}/glfw/include
    ${IMGUI_SRC_DIR}
    ${VULKAN_INCLUDE_DIR}
)

set_target_properties(${TARGET_NAME} PROPERTIES FOLDER Source/ThirdParty)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${IMGUI_SOURCES})
