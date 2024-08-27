
# set the name of project
project(demo)

# include
include_directories(.)

# add src
aux_source_directory(. SRCS)

# generate target
add_executable(${PROJECT_NAME} ${SRCS})

# link libary
target_link_libraries(
    ${PROJECT_NAME}
    unicstl
)

# install 
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
