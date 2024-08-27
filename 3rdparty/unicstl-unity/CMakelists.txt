
# set the name of project
project(unity)

file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

# add library
add_library(${PROJECT_NAME} STATIC ${SRCS})

# install 
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
