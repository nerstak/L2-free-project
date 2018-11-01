cmake_minimum_required(VERSION 3.7)
project(free_project C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wno-unused-parameter")

set(SRC
        main.c
        src/window.c
        src/launch.c
        src/game.c
        src/timer.c
        src/image.c
        src/scene.c
        src/scenes/mainMenu.c
        src/scenes/loadingScreen.c
        src/asset.c
        src/data.c
        src/player.c
        src/scenes/lobby.c
        src/ttf.c
        src/inventory.c
        src/scenes/shopScreen.c
        )

set(HDR
        src/window.h
        src/launch.h
        src/game.h
        src/timer.h
        src/image.h
        src/scene.h
        src/scenes/mainMenu.h
        src/scenes/loadingScreen.h
        src/asset.h
        src/data.h
        src/player.h
        src/scenes/lobby.h
        src/ttf.h
        src/inventory.h
        src/scenes/shopScreen.h
        )

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL_ttf REQUIRED)
find_package(SDL_mixer REQUIRED)

include_directories(${SDL_INCLUDE_DIRS} ${SDL_IMAGE_INCLUDE_DIRS} ${SDLTTF_INCLUDE_DIRS} ${SDL_MIXER_INCLUDE_DIRS})

add_executable(free_project  ${SRC} ${HDR})
target_link_libraries(free_project ${SDL_LIBRARY} ${SDL_IMAGE_LIBRARY} ${SDL_TTF_LIBRARY} ${SDL_MIXER_LIBRAIRY})