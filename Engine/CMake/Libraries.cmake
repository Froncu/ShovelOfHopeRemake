include(fetchcontent)
set(FETCHCONTENT_QUIET FALSE)

set(BUILD_SHARED_LIBS OFF)
fetchcontent_declare(SDL2
   GIT_REPOSITORY https://github.com/libsdl-org/SDL
   GIT_TAG release-2.30.11
   GIT_PROGRESS TRUE
   GIT_SHALLOW TRUE)
fetchcontent_makeavailable(SDL2)

fetchcontent_declare(SDL2_image
   GIT_REPOSITORY https://github.com/libsdl-org/SDL_image
   GIT_TAG release-2.8.4
   GIT_PROGRESS TRUE
   GIT_SHALLOW TRUE)
fetchcontent_makeavailable(SDL2_image)

set(SDL2TTF_VENDORED TRUE)
fetchcontent_declare(SDL2_ttf
   GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf
   GIT_TAG release-2.24.0
   GIT_PROGRESS TRUE
   GIT_SHALLOW TRUE)
fetchcontent_makeavailable(SDL2_ttf)

set(SDL2MIXER_VENDORED TRUE)
fetchcontent_declare(SDL2_mixer
   GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer
   GIT_TAG release-2.8.0
   GIT_PROGRESS TRUE
   GIT_SHALLOW TRUE)
fetchcontent_makeavailable(SDL2_mixer)

find_package(OpenGL REQUIRED)