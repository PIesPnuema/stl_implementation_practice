
cmake_minimum_required(VERSION 3.22) 
project(MYVECTOR) 

# Compile standards
set(CMAKE_CXX_STANDARD 23)				# what compiler we need
set(CMAKE_CXX_STANDARD_REQUIRED True)	# stating that we will require the above

# Creates Variables
set(SOURCES 
    ${PROJECT_SOURCE_DIR}/main.cpp)

# Sub directories (need to add, then include to target)
#add_subdirectory(src) # if library is needed.
add_subdirectory(UnitTest++/src)

# Makes path to headers discoverable to .cpp files
include_directories("${PROJECT_SOURCE_DIR}/include")

# executable main.cpp naming project executable.
add_executable(MYVECTOR ${SOURCES})

# adding libraries targets to project executable.
target_link_libraries(MYVECTOR PUBLIC UnitTest++)

# Adding directories to target.
target_include_directories(MYVECTOR PUBLIC 
						"${PROJECT_BINARY_DIR}"
						"${PROJECT_SOURCE_DIR}/UnitTest++/src")


