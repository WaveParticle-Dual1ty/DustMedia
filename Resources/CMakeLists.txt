# Copy Resources
set(TARGET_NAME COPY_RESOURCES)

add_custom_target(${TARGET_NAME}
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJ_RESOURCE_DIR}/Sandbox
        $<$<CONFIG:Debug>:${PROJ_OUTPUT_DIR_DEBUG}/Resources/Sandbox>$<$<CONFIG:Release>:${PROJ_OUTPUT_DIR_RELEASE}/Resources/Sandbox>
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJ_RESOURCE_DIR}/DustImageViewer
        $<$<CONFIG:Debug>:${PROJ_OUTPUT_DIR_DEBUG}/Resources/DustImageViewer>$<$<CONFIG:Release>:${PROJ_OUTPUT_DIR_RELEASE}/Resources/DustImageViewer>
)

set_target_properties(${TARGET_NAME} PROPERTIES FOLDER CustomTarget)

# Resources
set(TARGET_NAME Resources)
file(GLOB RESOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/Sandbox/Shaders/*.glsl
    ${CMAKE_CURRENT_SOURCE_DIR}/Sandbox/Images/*.png
    ${CMAKE_CURRENT_SOURCE_DIR}/DustImageViewer/Shaders/*.glsl
)
add_custom_target(${TARGET_NAME} ALL SOURCES ${RESOURCE_FILES})
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER Resources)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${RESOURCE_FILES})
