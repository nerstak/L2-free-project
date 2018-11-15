cmake_minimum_required(VERSION 3.7)
project(free_project C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wno-unused-parameter")

set(SRC
        main.c
        src/asset.c
        src/data.c
        src/game.c
        src/inventory.c
        src/launch.c
        src/layout.c
        src/player.c
        src/timer.c
        src/window.c
        src/engine/collectors/image.c
        src/engine/collectors/scene.c
        src/engine/collectors/ttf.c
        src/engine/main.c
        src/engine/save.c
        src/scenes/inventoryScreen/event.c
        src/scenes/inventoryScreen/inventoryScreen.c
        src/scenes/inventoryScreen/logic.c
        src/scenes/inventoryScreen/render.c
        src/scenes/loadingScreen/event.c
        src/scenes/loadingScreen/loadingScreen.c
        src/scenes/loadingScreen/logic.c
        src/scenes/loadingScreen/render.c
        src/scenes/lobby/event.c
        src/scenes/lobby/lobby.c
        src/scenes/lobby/logic.c
        src/scenes/lobby/render.c
        src/scenes/mainMenu/event.c
        src/scenes/mainMenu/logic.c
        src/scenes/mainMenu/mainMenu.c
        src/scenes/mainMenu/render.c
        src/scenes/shopScreen/event.c
        src/scenes/shopScreen/logic.c
        src/scenes/shopScreen/render.c
        src/scenes/shopScreen/shopScreen.c
        src/utils/coord.c
        src/utils/direction.c
        src/utils/math.c
        src/utils/queue.c
        src/utils/treemap.c
        src/dungeon/bounds.c
        src/dungeon/condition.c
        src/dungeon/edge.c
        src/dungeon/dungeon.c
        src/dungeon/room.c
        src/dungeon/symbol.c
        )

set(HDR
        src/asset.h
        src/data.h
        src/game.h
        src/inventory.h
        src/launch.h
        src/layout.h
        src/player.h
        src/timer.h
        src/window.h
        src/engine/collectors/image.h
        src/engine/collectors/scene.h
        src/engine/collectors/ttf.h
        src/engine/main.h
        src/engine/save.h
        src/scenes/inventoryScreen/event.h
        src/scenes/inventoryScreen/inventoryScreen.h
        src/scenes/inventoryScreen/logic.h
        src/scenes/inventoryScreen/render.h
        src/scenes/loadingScreen/event.h
        src/scenes/loadingScreen/loadingScreen.h
        src/scenes/loadingScreen/logic.h
        src/scenes/loadingScreen/render.h
        src/scenes/lobby/event.h
        src/scenes/lobby/lobby.h
        src/scenes/lobby/logic.h
        src/scenes/lobby/render.h
        src/scenes/mainMenu/event.h
        src/scenes/mainMenu/logic.h
        src/scenes/mainMenu/mainMenu.h
        src/scenes/mainMenu/render.h
        src/scenes/shopScreen/event.h
        src/scenes/shopScreen/logic.h
        src/scenes/shopScreen/render.h
        src/scenes/shopScreen/shopScreen.h
        src/structures/inventoryScreen.h
        src/structures/lobby.h
        src/structures/mainMenu.h
        src/structures/scene.h
        src/structures/shopScreen.h
        src/utils/coord.h
        src/utils/direction.h
        src/utils/math.h
        src/utils/queue.h
        src/utils/treemap.h
        src/dungeon/bounds.h
        src/dungeon/condition.h
        src/dungeon/edge.h
        src/dungeon/dungeon.h
        src/dungeon/room.h
        src/dungeon/symbol.h
        )

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL_ttf REQUIRED)
find_package(SDL_mixer REQUIRED)

include_directories(${SDL_INCLUDE_DIRS} ${SDL_IMAGE_INCLUDE_DIRS} ${SDLTTF_INCLUDE_DIRS} ${SDL_MIXER_INCLUDE_DIRS})

add_executable(free_project  ${SRC} ${HDR})
target_link_libraries(free_project ${SDL_LIBRARY} ${SDL_IMAGE_LIBRARY} ${SDL_TTF_LIBRARY} ${SDL_MIXER_LIBRAIRY} m)