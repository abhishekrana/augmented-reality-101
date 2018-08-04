# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (augrel101)

# set the C++ standard to C++ 11
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra")

############################################################
# Create an executable
############################################################
# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    src/main.cpp
)

# Add an executable with the above sources
add_executable(${PROJECT_NAME} ${SOURCES})


############################################################
# Add flags
############################################################
# Add the definition -DEX3 when compiling the target.
target_compile_definitions(${PROJECT_NAME}
    PRIVATE EX3
)

############################################################
# Include paths
############################################################
# These will be included as -I/directory/path/ for g++
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
		#${PROJECT_SOURCE_DIR}/lib/glew-2.1.0/install/include
		#${PROJECT_SOURCE_DIR}/lib/glfw-3.2.1/install/include
		#${PROJECT_SOURCE_DIR}/lib/glm/install/include
		#${Boost_INCLUDE_DIRS}
)


############################################################
# Link libraries
############################################################
#find_library(GLEW_LIBRARY GLEW HINTS /home/abhishek/Abhishek/git/augmented-reality-101/lib/glew-2.1.0/install/lib/)
#find_library(GLFW3_LIBRARY glfw3 HINTS /home/abhishek/Abhishek/git/augmented-reality-101/lib/glfw-3.2.1/install/lib/)
find_library(GLEW_LIBRARY GLEW)
find_library(GLFW3_LIBRARY glfw3)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
		${GLEW_LIBRARY}
		glfw3
        GL GLU X11 Xxf86vm Xrandr pthread Xi dl Xcursor Xinerama
		# ${GLFW3_LIBRARY}
		# ${PROJECT_SOURCE_DIR}/lib/glm/install/lib
		# ${PROJECT_SOURCE_DIR}/lib/glfw-3.2.1/install/lib
)
message("GLEW_LIBRARY: ${GLEW_LIBRARY}")
message("GLFW3_LIBRARY: ${GLFW3_LIBRARY}")


############################################################
# Print for debugging
############################################################

# Print all CMake variables defined and their values:
# get_cmake_property(_variableNames VARIABLES)
# list (SORT _variableNames)
# foreach (_variableName ${_variableNames})
#     message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()

# Print environment variables
execute_process(COMMAND "${CMAKE_COMMAND}" "-E" "environment")

