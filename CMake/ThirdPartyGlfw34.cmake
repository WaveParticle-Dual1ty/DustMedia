set(TARGET_NAME Third_glfw)

set(GLFW_SRC_DIR "${PROJ_THIRDPARTY_DIR}/glfw-3.4")

if (WIN32)
    set(GLFW_BUILD_WIN32 1)
    message(STATUS "GLFW using Win32 for window creation")
elseif (APPLE)
    set(GLFW_BUILD_COCOA 1)
    message(STATUS "GLFW using Apple for window creation")
else()
    message(FATAL_ERROR "Unsuport platform")
endif()

add_library(${TARGET_NAME} STATIC
    ${GLFW_SRC_DIR}/include/GLFW/glfw3.h
    ${GLFW_SRC_DIR}/include/GLFW/glfw3native.h
    ${GLFW_SRC_DIR}/src/internal.h
    ${GLFW_SRC_DIR}/src/platform.h
    ${GLFW_SRC_DIR}/src/mappings.h
    ${GLFW_SRC_DIR}/src/context.c
    ${GLFW_SRC_DIR}/src/init.c
    ${GLFW_SRC_DIR}/src/input.c
    ${GLFW_SRC_DIR}/src/monitor.c
    ${GLFW_SRC_DIR}/src/platform.c
    ${GLFW_SRC_DIR}/src/vulkan.c
    ${GLFW_SRC_DIR}/src/window.c
    ${GLFW_SRC_DIR}/src/egl_context.c
    ${GLFW_SRC_DIR}/src/osmesa_context.c
    ${GLFW_SRC_DIR}/src/null_platform.h
    ${GLFW_SRC_DIR}/src/null_joystick.h
    ${GLFW_SRC_DIR}/src/null_init.c
    ${GLFW_SRC_DIR}/src/null_monitor.c
    ${GLFW_SRC_DIR}/src/null_window.c
    ${GLFW_SRC_DIR}/src/null_joystick.c
)

if (APPLE)
    target_sources(${TARGET_NAME} PRIVATE
        ${GLFW_SRC_DIR}/src/cocoa_time.h
        ${GLFW_SRC_DIR}/src/cocoa_time.c
        ${GLFW_SRC_DIR}/src/posix_thread.h
        ${GLFW_SRC_DIR}/src/posix_module.c
        ${GLFW_SRC_DIR}/src/posix_thread.c
    )
elseif (WIN32)
    target_sources(${TARGET_NAME} PRIVATE
        ${GLFW_SRC_DIR}/src/win32_time.h
        ${GLFW_SRC_DIR}/src/win32_thread.h
        ${GLFW_SRC_DIR}/src/win32_module.c
        ${GLFW_SRC_DIR}/src/win32_time.c
        ${GLFW_SRC_DIR}/src/win32_thread.c
    )
else()
    target_sources(${TARGET_NAME} PRIVATE
        ${GLFW_SRC_DIR}/src/posix_time.h
        ${GLFW_SRC_DIR}/src/posix_thread.h
        ${GLFW_SRC_DIR}/src/posix_module.c
        ${GLFW_SRC_DIR}/src/posix_time.c
        ${GLFW_SRC_DIR}/src/posix_thread.c
    )
endif()

if (GLFW_BUILD_COCOA)
    target_compile_definitions(${TARGET_NAME} PRIVATE _GLFW_COCOA)
    target_sources(${TARGET_NAME} PRIVATE
        ${GLFW_SRC_DIR}/src/cocoa_platform.h
        ${GLFW_SRC_DIR}/src/cocoa_joystick.h
        ${GLFW_SRC_DIR}/src/cocoa_init.m
        ${GLFW_SRC_DIR}/src/cocoa_joystick.m
        ${GLFW_SRC_DIR}/src/cocoa_monitor.m
        ${GLFW_SRC_DIR}/src/cocoa_window.m
        ${GLFW_SRC_DIR}/src/nsgl_context.m
    )
endif()

if (GLFW_BUILD_WIN32)
    target_compile_definitions(${TARGET_NAME} PRIVATE _GLFW_WIN32)
    target_sources(${TARGET_NAME} PRIVATE
        ${GLFW_SRC_DIR}/src/win32_platform.h
        ${GLFW_SRC_DIR}/src/win32_joystick.h
        ${GLFW_SRC_DIR}/src/win32_init.c
        ${GLFW_SRC_DIR}/src/win32_joystick.c
        ${GLFW_SRC_DIR}/src/win32_monitor.c
        ${GLFW_SRC_DIR}/src/win32_window.c
        ${GLFW_SRC_DIR}/src/wgl_context.c
    )
endif()

if (GLFW_BUILD_COCOA)
    target_link_libraries(${TARGET_NAME} PRIVATE
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreFoundation"
    )
endif()

set_target_properties(${TARGET_NAME} PROPERTIES FOLDER Source/ThirdParty)