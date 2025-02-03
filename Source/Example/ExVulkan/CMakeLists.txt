set(TARGET_NAME ExVulkan)

include(${PROJ_DIR}/CMake/DependVulkan.cmake)

file(GLOB_RECURSE SRC_FILES "./*.h" "./*.cpp")
add_executable(${TARGET_NAME} ${SRC_FILES})

target_link_libraries(${TARGET_NAME} PRIVATE
    $<$<CONFIG:Debug>:${VULKAN_LIBS_DEBUG}>
    $<$<CONFIG:Release>:${VULKAN_LIBS_RELEASE}>
)

target_include_directories(${TARGET_NAME} PRIVATE
    ${VULKAN_INCLUDE_DIR}
)

set_target_properties(${TARGET_NAME} PROPERTIES FOLDER Source/Example)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC_FILES})

if(CMAKE_CXX_COMPILER MATCHES MSVC)
    set_target_properties(${TARGET_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
        $<$<CONFIG:Debug>:${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}>$<$<CONFIG:Release>:${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}>
    )
endif()

