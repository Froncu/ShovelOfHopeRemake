add_library(Engine STATIC
   Source/BaseGame.cpp
   Source/Matrix2x3.cpp
   Source/myutils.cpp
   Source/SoundEffect.cpp
   Source/SoundStream.cpp
   Source/structs.cpp
   Source/SVGParser.cpp
   Source/Texture.cpp
   Source/utils.cpp
   Source/Vector2f.cpp)

target_include_directories(Engine PUBLIC Include)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake)
include(Libraries)
target_link_libraries(Engine PUBLIC
   OpenGL::GL
   SDL2::SDL2
   SDL2main
   SDL2_ttf
   SDL2_image
   SDL2_mixer)