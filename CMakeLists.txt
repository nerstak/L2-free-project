cmake_minimum_required(VERSION 3.7)
project(free_project C)

set(CMAKE_C_STANDARD 99)

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL_ttf REQUIRED)
find_package(SDL_mixer REQUIRED)

include_directories(${SDL_INCLUDE_DIR} ${SDL_IMAGE_INCLUDE_DIR} ${SDL_TTF_INCLUDE_DIR} ${SDL_MIXER_INCLUDE_DIR})

add_executable(free_project main.c src/window.c src/window.h src/launch.c src/launch.h)
target_link_libraries(free_project ${SDL_LIBRARY} ${SDL_IMAGE_LIBRAIRIES} ${SDL_TTF_LIBRAIRIES} ${SDL_MIXER_LIBRAIRIES})