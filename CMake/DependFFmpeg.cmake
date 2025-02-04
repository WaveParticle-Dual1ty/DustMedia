# Depend FFmpeg

if(WIN32)
    set(FFMPEG_INCLUDE_DIR ${PROJ_DEPENDS_DIR}/FFmpeg/Windows/include)
    set(FFMPEG_LIB_DIR ${PROJ_DEPENDS_DIR}/FFmpeg/Windows/lib)
    set(FFMPEG_LIBS
        ${FFMPEG_LIB_DIR}/avutil.lib
        ${FFMPEG_LIB_DIR}/avformat.lib
        ${FFMPEG_LIB_DIR}/avcodec.lib
        ${FFMPEG_LIB_DIR}/swresample.lib
    )

    # Copy binary file to output directory
    set(FFMPEG_FILE_TO_COPY
        ${PROJ_DEPENDS_DIR}/FFmpeg/Windows/bin/avutil-59.dll
        ${PROJ_DEPENDS_DIR}/FFmpeg/Windows/bin/avformat-61.dll
        ${PROJ_DEPENDS_DIR}/FFmpeg/Windows/bin/avcodec-61.dll
        ${PROJ_DEPENDS_DIR}/FFmpeg/Windows/bin/swresample-5.dll
    )

    set(FFMPEG_DESTINATION_DIR_DEBUG "${PROJ_OUTPUT_DIR_DEBUG}")
    set(FFMPEG_DESTINATION_DIR_RELEASE "${PROJ_OUTPUT_DIR_RELEASE}")
    file(MAKE_DIRECTORY ${FFMPEG_DESTINATION_DIR_DEBUG})
    file(MAKE_DIRECTORY ${FFMPEG_DESTINATION_DIR_RELEASE})

    # todo: use custom target
    file(COPY ${FFMPEG_FILE_TO_COPY} DESTINATION ${FFMPEG_DESTINATION_DIR_DEBUG})
    file(COPY ${FFMPEG_FILE_TO_COPY} DESTINATION ${FFMPEG_DESTINATION_DIR_RELEASE})
elseif(APPLE)
    set(FFMPEG_INCLUDE_DIR ${PROJ_DEPENDS_DIR}/FFmpeg/Apple/include)
    set(FFMPEG_LIB_DIR ${PROJ_DEPENDS_DIR}/FFmpeg/Apple/lib)
    set(FFMPEG_LIBS
        ${FFMPEG_LIB_DIR}/libavutil.dylib
        ${FFMPEG_LIB_DIR}/libavformat.dylib
        ${FFMPEG_LIB_DIR}/libavcodec.dylib
        ${FFMPEG_LIB_DIR}/libswresample.dylib
    )
else()
    message(FATAL_ERROR "Unsuport platform Unknown")
endif()
