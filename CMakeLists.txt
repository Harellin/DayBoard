cmake_minimum_required(VERSION 3.16)

project(DayBoard LANGUAGES CXX)
set(CMAKE_PREFIX_PATH "C:/Qt/6.11.1/mingw_64")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# ---- Qt ----
find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)

# ---- Include directories ----
include_directories(
    ${CMAKE_SOURCE_DIR}/backend
    ${CMAKE_SOURCE_DIR}/backend/controllers
    ${CMAKE_SOURCE_DIR}/backend/core
    ${CMAKE_SOURCE_DIR}/backend/models
    ${CMAKE_SOURCE_DIR}/frontend
    ${CMAKE_SOURCE_DIR}/frontend/calendar
    ${CMAKE_SOURCE_DIR}/frontend/view
    ${CMAKE_SOURCE_DIR}/frontend/settings
)

# ---- Source files ----
file(GLOB_RECURSE SOURCES
    backend/**/*.cpp
    frontend/**/*.cpp
)

file(GLOB_RECURSE UI_FILES
    frontend/**/*.ui
)

# ---- Executable ----
qt_add_executable(DayBoard
    main.cpp
    ${SOURCES}
    ${UI_FILES}
)

# ---- Link Qt ----
target_link_libraries(DayBoard PRIVATE
    Qt6::Widgets
    Qt6::Core
    Qt6::Gui
)
