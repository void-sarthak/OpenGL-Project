cmake_minimum_required(VERSION 3.10)
project(OpenGLProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add GLAD source files
add_library(glad STATIC lib/glad/src/glad.c)
include_directories(include)

# Function to download a file
function(download_file url output)
    if(NOT EXISTS ${output})
        message(STATUS "Downloading ${url}")
        file(DOWNLOAD ${url} ${output})
    endif()
endfunction()

# Download and build GLFW
set(GLFW_VERSION 3.3.2)
set(GLFW_URL https://github.com/glfw/glfw/archive/${GLFW_VERSION}.zip)
set(GLFW_SOURCE_DIR ${CMAKE_BINARY_DIR}/glfw-src/glfw-${GLFW_VERSION})
set(GLFW_BUILD_DIR ${CMAKE_BINARY_DIR}/glfw-build)
set(GLFW_INSTALL_DIR ${CMAKE_BINARY_DIR}/glfw-install)

download_file(${GLFW_URL} ${CMAKE_BINARY_DIR}/glfw-${GLFW_VERSION}.zip)
file(ARCHIVE_EXTRACT INPUT ${CMAKE_BINARY_DIR}/glfw-${GLFW_VERSION}.zip DESTINATION ${GLFW_SOURCE_DIR})

# Build GLFW
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(${GLFW_SOURCE_DIR} ${GLFW_BUILD_DIR})

include_directories(${GLFW_SOURCE_DIR}/include)
include_directories(${GLFW_INSTALL_DIR}/include)

# Add platform-specific libraries
if (WIN32)
    set(PLATFORM_LIBS ${CMAKE_DL_LIBS})
elseif (APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(CORE_FOUNDATION_LIBRARY CoreFoundation)
    find_library(CORE_VIDEO_LIBRARY CoreVideo)
    set(PLATFORM_LIBS ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${CORE_FOUNDATION_LIBRARY} ${CORE_VIDEO_LIBRARY})
else()
    set(PLATFORM_LIBS dl)
endif()

# Add source files
set(SOURCES 
    src/main.cpp 
    src/Shader.cpp
)

# Add include directories
include_directories(include)  # Ensure include directory is included for shader.h

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link GLFW, GLAD, and platform-specific libraries
target_link_libraries(${PROJECT_NAME} glad glfw ${PLATFORM_LIBS})
