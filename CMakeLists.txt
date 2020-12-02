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
set(GLES2_LIBS GLESv2 glfw)

endif(UNIX)



add_executable(Basic
  ${PROJECT_HOME}/main.cpp

  ${PROJECT_HOME}/system/Log.cpp
  ${PROJECT_HOME}/system/GLFW_Platform
  ${PROJECT_HOME}/support/src/glad.c
  ${PROJECT_HOME}/system/Primitives/ESShaderRepository.cpp
  ${PROJECT_HOME}/system/Primitives/RenderPacket.cpp
  #${PROJECT_HOME}/debug_new.cpp

  ${PROJECT_HOME}/ShapeDrawing.cpp
)

target_link_libraries(Basic ${GLES2_LIBS} )
target_include_directories(Basic PUBLIC
  ${PROJECT_HOME}/system
  ${PROJECT_HOME}/system/Primitives
  ${PROJECT_HOME}/support/include
)
target_compile_definitions(Basic PUBLIC GLFW_INCLUDE_ES2)

