set(target "${PHOTOEFFECTS_TESTS}")

FILE(GLOB hdrs "*.h*")
FILE(GLOB srcs "*.cpp")

# INCLUDE_DIRECTORIES("${OpenCV_SOURCE_PATH}/modules/ts/include")
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/gtest")

ADD_EXECUTABLE(${target} ${srcs} ${hdrs})
TARGET_LINK_LIBRARIES(${target} gtest ${PHOTOEFFECTS_LIBRARY})

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ln -fns "${CMAKE_CURRENT_SOURCE_DIR}/images " "${CMAKE_CURRENT_BINARY_DIR}/../images"
    #COMMAND ln -fns "${CMAKE_CURRENT_SOURCE_DIR}/images " "images"
)

# FIXME: check if we need it (Kirill Kornyakov)
set_target_properties(${target} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../"
    )
