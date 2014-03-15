set(target ${PHOTOEFFECTS_SAMPLE})

FILE(GLOB hdrs "*.h*")
FILE(GLOB srcs "*.cpp")

ADD_EXECUTABLE(${target} ${srcs} ${hdrs})
ADD_DEPENDENCIES(${target} ${PHOTOEFFECTS_LIBRARY})
TARGET_LINK_LIBRARIES(${target} ${PHOTOEFFECTS_LIBRARY})

# FIXME: check if we need it (Kirill Kornyakov)
set_target_properties(${target} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../"
    )
