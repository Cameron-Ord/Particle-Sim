cmake_minimum_required(VERSION 3.16)
project(Particle-Sim VERSION 1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

if(WIN32)
  set(CMAKE_REQUIRED_FLAGS "-lmingw32 -lSDL2main -lSDL2")
else()
  set(CMAKE_REQUIRED_FLAGS "-lSDL2")
endif()

find_library(SDL2_LIBRARY NAMES SDL2)
find_library(SDL2_LIBRARY_MAIN NAMES SDL2main)

message("")
if(NOT SDL2_LIBRARY_MAIN)
  message(WARNING "SDL2main not found!")
else()
  message(STATUS "SDL2main found at ${SDL2_LIBRARY_MAIN}")
endif()

if(NOT SDL2_LIBRARY)
  message(FATAL_ERROR "SDL2 not found, please install it via your package manager!")
else()
  message(STATUS "SDL2 found at ${SDL2_LIBRARY}")
endif()
message("")

file(GLOB SOURCES "src/*.c")

if(WIN32)
  add_executable(Vis WIN32 ${SOURCES})
else()
  add_executable(Vis ${SOURCES})
endif()

if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
  target_compile_options(Vis PRIVATE -Wall -Wextra -pedantic)
endif()

if(WIN32)
  target_include_directories(Vis PUBLIC "C:/msys64/mingw64/include")
  target_compile_definitions(Vis PUBLIC SDL_MAIN_HANDLED)
  target_link_libraries(Vis ${SDL2_LIBRARY_MAIN} ${SDL2_LIBRARY})
else()
  target_link_libraries(Vis ${SDL2_LIBRARY})
endif()
