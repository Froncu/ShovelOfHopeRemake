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

set_target_properties(Engine PROPERTIES
   CXX_STANDARD 14
   CXX_STANDARD_REQUIRED TRUE)

target_include_directories(Engine PUBLIC Include)

find_package(OpenGL REQUIRED)
find_package(SDL2 CONFIG REQUIRED COMPONENTS SDL2-static)
find_package(SDL2_image CONFIG REQUIRED COMPONENTS SDL2_image-static)
find_package(SDL2_ttf CONFIG REQUIRED COMPONENTS SDL2_ttf-static)
find_package(SDL2_mixer CONFIG REQUIRED COMPONENTS SDL2_mixer-static)

target_link_libraries(Engine PUBLIC
   OpenGL::GL
   SDL2::SDL2-static
   SDL2::SDL2main
   SDL2_image::SDL2_image-static
   SDL2_ttf::SDL2_ttf-static
   SDL2_mixer::SDL2_mixer-static)