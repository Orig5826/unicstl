
# set the name of project
project(unicstl)

# add src
aux_source_directory(. SRCS)

# generate library
add_library(${PROJECT_NAME} STATIC ${SRCS})

# install
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
