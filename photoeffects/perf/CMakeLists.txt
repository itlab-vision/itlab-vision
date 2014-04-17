set(target "${PHOTOEFFECTS_PERF}")

FILE(GLOB hdrs "*.h*")
FILE(GLOB srcs "*.cpp")

INCLUDE_DIRECTORIES("${OpenCV_SOURCE_PATH}/modules/ts/include")

ADD_EXECUTABLE(${target} ${srcs} ${hdrs})
TARGET_LINK_LIBRARIES(${target} ${PHOTOEFFECTS_LIBRARY})

add_custom_command(
    TARGET ${PHOTOEFFECTS_PERF}
    POST_BUILD
    COMMAND ln -fns "${CMAKE_SOURCE_DIR}/testdata" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/testdata"
    COMMENT "Adding a symbolic link to testdata"
)
