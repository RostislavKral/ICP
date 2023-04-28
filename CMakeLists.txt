cmake_minimum_required(VERSION 3.1)

project(MyQtProject)

# Find the required Qt libraries
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

include_directories(${Qt5Core_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS})

# Set the source files for the project
set(SOURCES
        src/main.cpp
        src/GameMap.cpp src/Player.cpp  src/GameReplay.cpp src/Player.cpp src/GUI.cpp src/Ghost.cpp src/Ghost.h src/GuiComponents.cpp )

# Set the header files for the project
set(HEADERS
        src/GameMap.h src/Player.h src/ImageHandler.cpp src/ImageHandler.h  src/GameReplay.h src/Coordinates.h src/GUI.h src/Ghost.cpp src/Ghost.h src/GuiComponents.h )


# Add the Qt include directories to the include path
include_directories(${Qt5Core_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS})

# Add the executable target
add_executable(MyQtProject ${SOURCES} ${HEADERS})

# Add the Qt libraries to the linker
target_link_libraries(MyQtProject Qt5::Core Qt5::Widgets)