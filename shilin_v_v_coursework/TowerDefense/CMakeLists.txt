cmake_minimum_required(VERSION 3.15)

project(TowerDefense LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
option(BUILD_WITH_DOCS "Build with documentation." OFF)

SET(CMAKE_INSTALL_PREFIX $<TARGET_FILE_DIR:${PROJECT_NAME}> CACHE PATH "Initial cahe" FORCE)

if (CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Debug or Release" FORCE)
else()
  if (NOT CMAKE_BUILT_TYPE)
    message("Defaulting to release build.")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Default: Release" FORCE)
  endif()
  set_property(CAHCE CMAKE_BUILD_TYPE PROPERTY HELPSTRING "Choose the type of buiild")
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug;Release")
endif()

set(prj_headers
    Bullet.h
    Clickable.h
    Enemy.h
    EnemyController.h
    GameController.h
    GameMenuController.h
    GameState.h
    MenuButton.h
    Timer.h
    Tower.h
    BulletController.h
    TowerButton.h
    TowerController.h
)

set(prj_sources
    Bullet.cpp
    Clickable.cpp
    Enemy.cpp
    EnemyController.cpp
    GameController.cpp
    GameMenuController.cpp
    GameState.cpp
    MenuButton.cpp
    Timer.cpp
    Tower.cpp
    BulletController.cpp
    TowerButton.cpp
    TowerController.cpp
)

if (BUILD_WITH_DOCS)
  add_subdirectory(doc)
endif()

add_executable(${PROJECT_NAME} 
${prj_sources} 
${prj_headers})

find_package(SFML COMPONENTS audio graphics window system REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC sfml-graphics sfml-audio sfml-window sfml-system)

if (WIN32)
  get_filename_component(binDIR ${SFML_DIR} DIRECTORY)
  get_filename_component(binDIR ${binDIR} DIRECTORY)
  get_filename_component(binDIR ${binDIR} DIRECTORY)
  set(binDIR ${binDIR}/bin)
  set(debDIR ${CMAKE_BINARY_DIR}/Debug)
  set(relDIR ${CMAKE_BINARY_DIR}/Release)
  install(FILES "${binDIR}/openal32.dll" DESTINATION ${debDIR})
  install(FILES "${binDIR}/openal32.dll" DESTINATION ${relDIR})
  install(FILES "${binDIR}/sfml-audio-d-2.dll" DESTINATION ${debDIR})
  install(FILES "${binDIR}/sfml-audio-2.dll" DESTINATION ${relDIR})
  install(FILES "${binDIR}/sfml-graphics-d-2.dll" DESTINATION ${debDIR})
  install(FILES "${binDIR}/sfml-graphics-2.dll" DESTINATION ${relDIR})
  install(FILES "${binDIR}/sfml-system-d-2.dll" DESTINATION ${debDIR})
  install(FILES "${binDIR}/sfml-system-2.dll" DESTINATION ${relDIR})
  install(FILES "${binDIR}/sfml-window-d-2.dll" DESTINATION ${debDIR})
  install(FILES "${binDIR}/sfml-window-2.dll" DESTINATION ${relDIR})
else()
  install(FILES $<TARGET_FILE:sfml-graphics> DESTINATION $<TARGET_FILE_DIR:${PROJECT_NAME}>)
  install(FILES $<TARGET_FILE:sfml-audio> DESTINATION $<TARGET_FILE_DIR:${PROJECT_NAME}>)
  install(FILES $<TARGET_FILE:sfml-window> DESTINATION $<TARGET_FILE_DIR:${PROJECT_NAME}>)
  install(FILES $<TARGET_FILE:sfml-system> DESTINATION $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()

file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/font DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/images DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/music DESTINATION ${CMAKE_BINARY_DIR})