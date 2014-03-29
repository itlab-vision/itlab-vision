set(target ${PHOTOEFFECTS_SAMPLE})

FILE(GLOB hdrs "*.h*")
FILE(GLOB srcs "${PHOTOEFFECTS_SAMPLE}.cpp")

ADD_EXECUTABLE(${target} ${srcs} ${hdrs})
ADD_DEPENDENCIES(${target} ${PHOTOEFFECTS_LIBRARY})
TARGET_LINK_LIBRARIES(${target} ${PHOTOEFFECTS_LIBRARY})

# FIXME: check if we need it (Kirill Kornyakov)
set_target_properties(${target} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../"
    )
set(fadeColor_target ${FADECOLOR_SAMPLE})

FILE(GLOB ${FADECOLOR_SAMPLE}_hdrs "*.h*")
FILE(GLOB ${FADECOLOR_SAMPLE}_srcs "${FADECOLOR_SAMPLE}.cpp")

ADD_EXECUTABLE(${fadeColor_target} ${${FADECOLOR_SAMPLE}_srcs} ${${FADECOLOR_SAMPLE}_hdrs})
ADD_DEPENDENCIES(${fadeColor_target} ${PHOTOEFFECTS_LIBRARY})
TARGET_LINK_LIBRARIES(${fadeColor_target} ${PHOTOEFFECTS_LIBRARY})

# FIXME: check if we need it (Kirill Kornyakov)
set_target_properties(${fadeColor_target} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../"
    )
