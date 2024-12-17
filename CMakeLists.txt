cmake_minimum_required(VERSION 3.18.0)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_BUILD_TYPE Debug)

if(APPLE OR UNIX)
  set(CMAKE_C_COMPILER "gcc")
  set(CMAKE_CXX_COMPILER "g++")
endif()

set(CMAKE_CXX_STANDARD_REQUIRED 20)

project(gameboy LANGUAGES CXX)

add_executable(gameboy src/main.cpp)

add_executable(
  emulator_tests
  src/tests/main.cpp
  src/tests/memory.cpp
  src/tests/cartridge.cpp
  src/tests/mapper.cpp
  src/tests/cpu.cpp
  src/tests/ppu.cpp
  src/tests/runner.cpp)

add_library(
  emulator
  src/emulator/cpu/cpu.cpp
  src/emulator/cpu/opcodes.cpp
  src/emulator/cpu/instructions.cpp
  src/emulator/cpu/tables.cpp
  src/emulator/memory/memory.cpp
  src/emulator/memory/cartridge.cpp
  src/emulator/memory/mapper.cpp
  src/emulator/ppu/ppu.cpp
  src/emulator/runner/runner.cpp
  src/emulator/runner/joypad.cpp
  src/emulator/runner/debug_panels.cpp)

add_library(
  imgui
  lib/imgui/imgui_draw.cpp
  lib/imgui/imgui_tables.cpp
  lib/imgui/imgui.cpp
  lib/imgui/imgui_widgets.cpp
  lib/imgui/backends/imgui_impl_sdl2.cpp
  lib/imgui/backends/imgui_impl_sdlrenderer2.cpp
  lib/imgui/imgui_demo.cpp)

set(TARGETS gameboy emulator emulator_tests)

foreach(TARGET IN LISTS TARGETS)
  if(MSVC)
    # target_compile_options(${TARGET} PRIVATE /W4)
    target_compile_options(${TARGET} PRIVATE /O2)
  else()
    # target_compile_options(${TARGET} PRIVATE -Wall -Wextra -Wpedantic))
    target_compile_options(${TARGET} PRIVATE -O2)
  endif()
endforeach()

find_package(SDL2 REQUIRED)

if(WIN32 AND MSVC)
  set_target_properties(gameboy PROPERTIES LINK_FLAGS /SUBSYSTEM:CONSOLE)
  set(SDL2_DIR lib/SDL2/cmake)
  set(SDL2_ttf_DIR lib/SDL2_ttf/cmake)
  file(COPY lib/SDL2/lib/x64/SDL2.dll DESTINATION ${CMAKE_SOURCE_DIR}/bin)
  target_include_directories(gameboy PRIVATE lib/SDL2/include)
  target_include_directories(imgui PRIVATE lib/SDL2/include)
elseif(APPLE)
  target_include_directories(gameboy
                             PRIVATE ${SDL2_INCLUDE_DIRS})
  target_include_directories(imgui PRIVATE ${SDL2_INCLUDE_DIRS})
endif()

set_target_properties(
  ${TARGETS}
  PROPERTIES CXX_STANDARD 20
             ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
             LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
             RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

target_include_directories(imgui PRIVATE lib/imgui lib/imgui/backends)
target_include_directories(
  emulator
  PUBLIC src/emulator
         src/emulator/memory
         src/emulator/cpu
         src/emulator/ppu
         src/emulator/runner
         src/emulator/tests
         lib/imgui
         lib/imgui/backends)
target_link_libraries(emulator PUBLIC SDL2::SDL2 SDL2::SDL2main imgui)
target_link_libraries(gameboy PRIVATE emulator)
target_link_libraries(emulator_tests PRIVATE emulator)