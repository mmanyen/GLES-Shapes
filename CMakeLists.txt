cmake_minimum_required(VERSION 3.6.0)
project(ShapeDemo VERSION 0.0.2)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# define the absolute path to this directory for the rest of the tree to reference
get_filename_component(PROJECT_HOME . ABSOLUTE)


# Set compiler definations/options for each target
# These will apply to all included directories
if(WIN32)
add_definitions(
  -DPLATFORM_WINDOWS
  -D_CRT_SECURE_NO_WARNINGS
)
set(GLES2_LIBS ${PROJECT_HOME}/support/lib/glfw3.lib opengl32)

endif(WIN32)


if(UNIX)
add_definitions(
  -DPLATFORM_LINUX
)
#set(GLES2_LIBS GLESv2 glfw)

endif(UNIX)

cmake_policy(SET CMP0115 OLD)

add_executable(Basic
  ${PROJECT_HOME}/main.cpp

  ${PROJECT_HOME}/system/src/base/Log.cpp
  ${PROJECT_HOME}/system/src/base/GLFW_Platform.cpp
  ${PROJECT_HOME}/support/src/glad.c
  ${PROJECT_HOME}/system/src/base/ESShaderRepository.cpp
  ${PROJECT_HOME}/system/src/base/RenderPacket.cpp

  ${PROJECT_HOME}/system/src/primitives/ShapeDrawing.cpp
)

target_link_libraries(Basic ${GLES2_LIBS} )
target_include_directories(Basic PUBLIC
  ${PROJECT_HOME}/system/src/base
  ${PROJECT_HOME}/system/src/primitives
  ${PROJECT_HOME}/support/include
  ${PROJECT_HOME}/system/include
)
target_compile_definitions(Basic PUBLIC GLFW_INCLUDE_ES2)

