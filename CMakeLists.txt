cmake_minimum_required(VERSION 3.0.0)
project(SnakesDungeonAdventures VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(SnakesDungeonAdventures
    code/Config.h
    code/AbstractionsUtils.h
    code/AbstractionsUtils.cpp
    code/BaseEntities.h
    code/BaseEntities.cpp
    code/Spawner.h
    code/Spawner.cpp
    code/Engine.h
    code/Engine.cpp
    code/AppleSpawner.h
    code/AppleSpawner.cpp
    code/Snake.h
    code/Snake.cpp
    code/Apple.h
    code/Apple.cpp
    main.cpp
)

add_compile_options(--std=gnu++20)

target_link_libraries(SnakesDungeonAdventures pthread)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
