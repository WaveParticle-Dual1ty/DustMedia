set(TARGET_NAME Third_stb)

set(STB_SRC_DIR ${PROJ_THIRDPARTY_DIR}/stb)

set(STB_SOURCES
    ${STB_SRC_DIR}/stb.cpp
    ${STB_SRC_DIR}/stb_image.h
)

add_library(${TARGET_NAME} STATIC ${STB_SOURCES})
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER Source/ThirdParty)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${STB_SOURCES})