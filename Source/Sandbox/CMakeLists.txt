set(TARGET_NAME Sandbox)

file(GLOB_RECURSE SRC_FILES "./*.h" "./*.cpp")
add_executable(${TARGET_NAME} ${SRC_FILES})
target_link_libraries(${TARGET_NAME} PRIVATE
    MediaEngine
)

set_target_properties(${TARGET_NAME} PROPERTIES FOLDER Source)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC_FILES})

if(CMAKE_CXX_COMPILER MATCHES MSVC)
    set_target_properties(${TARGET_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
        $<$<CONFIG:Debug>:${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}>$<$<CONFIG:Release>:${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}>
    )
endif()

