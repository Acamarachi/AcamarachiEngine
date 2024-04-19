cmake_minimum_required(VERSION 3.11)
project(AcamarachiEngine VERSION 0.1.0 LANGUAGES CXX)

include(FetchContent)

# Enable Hot Reload for MSVC compilers if supported.
if(POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Define Core sources list
set(ACAMARACHi_CORE_SOURCES)
add_subdirectory(src/Core)

set(
  ACAMARACHi_MATHS_SOURCES
  ${CMAKE_SOURCE_DIR}/src/maths/vector.hpp
  ${CMAKE_SOURCE_DIR}/src/maths/matrix.hpp
  ${CMAKE_SOURCE_DIR}/src/maths/linear.hpp 
  ${CMAKE_SOURCE_DIR}/src/maths/linear.cpp 
  ${CMAKE_SOURCE_DIR}/src/maths/vector.cpp 
  ${CMAKE_SOURCE_DIR}/src/maths/matrix.cpp
)

add_executable(${PROJECT_NAME})
target_sources(
  ${PROJECT_NAME}
  PRIVATE

  ${CMAKE_SOURCE_DIR}/src/main.cpp
  ${CMAKE_SOURCE_DIR}/src/types.h
  ${CMAKE_SOURCE_DIR}/src/platform.h
  ${CMAKE_SOURCE_DIR}/src/config.h
  ${CMAKE_SOURCE_DIR}/src/macros.h
  ${ACAMARACHi_CORE_SOURCES}
  ${ACAMARACHi_MATHS_SOURCES}
)

#add build property
set_target_properties(${PROJECT_NAME} PROPERTIES
  CXX_STANDARD 17
  CXX_EXTENSIONS OFF
  COMPILE_WARNING_AS_ERROR ON
)

# Compiler-specific options
if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

#add external library

# Find Vulkan Path using CMake's Vulkan Module
# It is mandatory since we need both the headers and SDK
# Reference to the instalation guide if needed
find_package(Vulkan REQUIRED)

IF (NOT Vulkan_FOUND)
	message(FATAL_ERROR "Could not find Vulkan library!")
ELSE()
	message(STATUS ${Vulkan_LIBRARY})
ENDIF()

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw
  GIT_TAG master
)
FetchContent_MakeAvailable(glfw)

target_link_libraries(${PROJECT_NAME} PUBLIC Vulkan::Vulkan)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
