set(TARGET_NAME MediaEngine)

file(GLOB_RECURSE SRC_FILES "./*.h" "./*.cpp")
add_library(${TARGET_NAME} STATIC ${SRC_FILES})
target_link_libraries(${TARGET_NAME} PRIVATE
    Third_spdlog
)

set_target_properties(${TARGET_NAME} PROPERTIES FOLDER Source)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC_FILES})
