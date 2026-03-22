cmake_minimum_required(VERSION 3.15)
project(SfmlInvaders LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_executable(SfmlInvaders main.cpp Coin.cpp
        definitions.h
        Player.cpp
        Background.cpp
        Score.cpp)

target_link_libraries(SfmlInvaders PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
)

add_custom_command(TARGET SfmlInvaders POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:SfmlInvaders>/assets
)