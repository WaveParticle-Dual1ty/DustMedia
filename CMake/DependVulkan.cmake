# Depend Vulkan

if(WIN32)
    set(VULKAN_PATH $ENV{VK_SDK_PATH})
    if(NOT EXISTS ${VULKAN_PATH})
        message(FATAL_ERROR "Please set VULKAN_PATH")
    endif()
    message("Vulkan SDK directory = ${VULKAN_PATH}")

    set(VULKAN_INCLUDE_DIR ${VULKAN_PATH}/Include)
    set(VULKAN_LIB_DIR ${VULKAN_PATH}/Lib)
    set(VULKAN_BIN_DIR ${VULKAN_PATH}/Bin)
    set(VULKAN_LIBS_DEBUG
        ${VULKAN_LIB_DIR}/vulkan-1.lib
        ${VULKAN_LIB_DIR}/shaderc_sharedd.lib
        ${VULKAN_LIB_DIR}/spirv-cross-cored.lib
        ${VULKAN_LIB_DIR}/spirv-cross-glsld.lib
        ${VULKAN_LIB_DIR}/SDL2.lib
    )
    set(VULKAN_LIBS_RELEASE
        ${VULKAN_LIB_DIR}/vulkan-1.lib
        ${VULKAN_LIB_DIR}/shaderc_shared.lib
        ${VULKAN_LIB_DIR}/spirv-cross-core.lib
        ${VULKAN_LIB_DIR}/spirv-cross-glsl.lib
        ${VULKAN_LIB_DIR}/SDL2.lib
    )
elseif(APPLE)
    set(VULKAN_PATH ${PROJ_DEPENDS_DIR}/VulkanSDK/Apple)
    set(VULKAN_INCLUDE_DIR ${VULKAN_PATH}/include)
    set(VULKAN_LIB_DIR ${VULKAN_PATH}/lib)
    set(VULKAN_BIN_DIR ${VULKAN_PATH}/bin)
    set(VULKAN_LIBS_DEBUG
        ${VULKAN_LIB_DIR}/libvulkan.dylib
        ${VULKAN_LIB_DIR}/libshaderc_shared.dylib
        ${VULKAN_LIB_DIR}/libspirv-cross-core.a
        ${VULKAN_LIB_DIR}/libspirv-cross-glsl.a
    )
    set(VULKAN_LIBS_RELEASE
        ${VULKAN_LIB_DIR}/libvulkan.dylib
        ${VULKAN_LIB_DIR}/libshaderc_shared.dylib
        ${VULKAN_LIB_DIR}/libspirv-cross-core.a
        ${VULKAN_LIB_DIR}/libspirv-cross-glsl.a
    )
else()
    message(FATAL_ERROR "Unsuport platform Unknown")
endif()
