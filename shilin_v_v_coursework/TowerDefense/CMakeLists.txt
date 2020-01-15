cmake_minimum_required(VERSION 3.15)

project(TowerDefense LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
option(BUILD_WITH_DOCS "Build with documentation." OFF)

SET(CMAKE_INSTALL_PREFIX $<TARGET_FILE_DIR:${PROJECT_NAME}> CACHE PATH "Initial cahe" FORCE)

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
#install(FILES $<TARGET_FILE:sfml-graphics> DESTINATION $<TARGET_FILE_DIR:${PROJECT_NAME}>)
#install(FILES $<TARGET_FILE:sfml-audio> DESTINATION $<TARGET_FILE_DIR:${PROJECT_NAME}>)
#install(FILES $<TARGET_FILE:sfml-window> DESTINATION $<TARGET_FILE_DIR:${PROJECT_NAME}>)
#install(FILES $<TARGET_FILE:sfml-system> DESTINATION $<TARGET_FILE_DIR:${PROJECT_NAME}>)
get_filename_component(libDIR ${SFML_DIR} DIRECTORY)
get_filename_component(libDIR ${libDIR} DIRECTORY)
get_filename_component(libDIR $(libDIR} DIRECTORY)
#install(FILES "${libDIR}/bin/openal32.dll" DESTINATION $<TARGET_FILE_DIR:${PROJECT_NAME}>)
install(DIRECTORY "${libDIR}/bin/" DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/font DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/images DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/music DESTINATION ${CMAKE_BINARY_DIR})