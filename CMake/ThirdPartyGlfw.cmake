set(TARGET_NAME Third_glfw)

set(GLFW_SRC_DIR ${PROJ_THIRDPARTY_DIR}/glfw)

if (WIN32)
    set(_GLFW_WIN32 1)
    message(STATUS "GLFW using Win32 for window creation")
elseif (APPLE)
    set(_GLFW_COCOA 1)
    message(STATUS "GLFW using Apple for window creation")
else()
    message(FATAL_ERROR "Unsuport platform")
endif()

configure_file(${GLFW_SRC_DIR}/src/glfw_config.h.in glfw/src/glfw_config.h @ONLY)

set(GLFW_COMMOM_HEADERS
    ${CMAKE_CURRENT_BINARY_DIR}/glfw/src/glfw_config.h
    ${GLFW_SRC_DIR}/src/internal.h
    ${GLFW_SRC_DIR}/include/GLFW/glfw3.h
    ${GLFW_SRC_DIR}/include/GLFW/glfw3native.h
)

set(GLFW_COMMON_SOURCES
    ${GLFW_SRC_DIR}/src/context.c
    ${GLFW_SRC_DIR}/src/init.c
    ${GLFW_SRC_DIR}/src/input.c
    ${GLFW_SRC_DIR}/src/monitor.c
    ${GLFW_SRC_DIR}/src/vulkan.c
    ${GLFW_SRC_DIR}/src/window.c
)

if (_GLFW_WIN32)
    set(GLFW_HEADERS
        ${GLFW_COMMOM_HEADERS}
        ${GLFW_SRC_DIR}/src/win32_platform.h
        ${GLFW_SRC_DIR}/src/win32_joystick.h
        ${GLFW_SRC_DIR}/src/wgl_context.h
        ${GLFW_SRC_DIR}/src/egl_context.h
    )

    set(GLFW_SOURCES
        ${GLFW_COMMON_SOURCES}
        ${GLFW_SRC_DIR}/src/win32_init.c
        ${GLFW_SRC_DIR}/src/win32_joystick.c
        ${GLFW_SRC_DIR}/src/win32_monitor.c
        ${GLFW_SRC_DIR}/src/win32_time.c
        ${GLFW_SRC_DIR}/src/win32_tls.c
        ${GLFW_SRC_DIR}/src/win32_window.c
        ${GLFW_SRC_DIR}/src/wgl_context.c
        ${GLFW_SRC_DIR}/src/egl_context.c
    )

    set(GLFW_LIBRARIES)
elseif(_GLFW_COCOA)
    set(GLFW_HEADERS
        ${GLFW_COMMOM_HEADERS}
        ${GLFW_SRC_DIR}/src/cocoa_platform.h
        ${GLFW_SRC_DIR}/src/cocoa_joystick.h
        ${GLFW_SRC_DIR}/src/posix_tls.h
        ${GLFW_SRC_DIR}/src/nsgl_context.h
    )

    set(GLFW_SOURCES
        ${GLFW_COMMON_SOURCES}
        ${GLFW_SRC_DIR}/src/cocoa_init.m
        ${GLFW_SRC_DIR}/src/cocoa_joystick.m
        ${GLFW_SRC_DIR}/src/cocoa_monitor.m
        ${GLFW_SRC_DIR}/src/cocoa_window.m
        ${GLFW_SRC_DIR}/src/cocoa_time.c
        ${GLFW_SRC_DIR}/src/posix_tls.c
        ${GLFW_SRC_DIR}/src/nsgl_context.m
    )

    find_library(COCOA_FRAMEWORK Cocoa)
    find_library(IOKIT_FRAMEWORK IOKit)
    find_library(CORE_FOUNDATION_FRAMEWORK CoreFoundation)
    find_library(CORE_VIDEO_FRAMEWORK CoreVideo)
    list(APPEND GLFW_LIBRARIES
        "${COCOA_FRAMEWORK}"
        "${IOKIT_FRAMEWORK}"
        "${CORE_FOUNDATION_FRAMEWORK}"
        "${CORE_VIDEO_FRAMEWORK}"
    )
endif()

add_library(${TARGET_NAME} STATIC ${GLFW_HEADERS} ${GLFW_SOURCES})
target_include_directories(${TARGET_NAME} PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}/glfw/src
    ${GLFW_SRC_DIR}/src
)
target_link_libraries(${TARGET_NAME} PRIVATE ${GLFW_LIBRARIES})
target_compile_definitions(${TARGET_NAME} PRIVATE -D_GLFW_USE_CONFIG_H)
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER Source/ThirdParty)
