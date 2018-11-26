cmake_minimum_required(VERSION 3.7)
project(free_project C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wno-unused-parameter")

FILE(GLOB_RECURSE SRC "src/*.c")
FILE(GLOB_RECURSE HDR "src/*.h")

set(MAIN main.c)

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL_ttf REQUIRED)
find_package(SDL_mixer REQUIRED)

include_directories(${SDL_INCLUDE_DIRS} ${SDL_IMAGE_INCLUDE_DIRS} ${SDLTTF_INCLUDE_DIRS} ${SDL_MIXER_INCLUDE_DIRS})

add_executable(free_project ${MAIN} ${SRC} ${HDR})
target_link_libraries(free_project ${SDL_LIBRARY} ${SDL_IMAGE_LIBRARY} ${SDL_TTF_LIBRARY} ${SDL_MIXER_LIBRARY} m)