# Specify the directory containing the header files
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Add the header files to the project
file(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

# Make the header files visible to other parts of the project
set(HEADER_FILES ${HEADER_FILES} PARENT_SCOPE)
