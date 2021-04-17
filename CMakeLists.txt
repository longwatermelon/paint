cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)

cmake_policy(SET CMP0091 NEW)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

project(paint)

add_executable(paint
	src/main.cpp
	src/paint.cpp
	src/settings.cpp
	src/graphics.cpp
	include/paint.h
	include/graphics.h
	include/utils.h
	include/settings.h
)

set_property(TARGET paint PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})


find_library(SDL2_LIB
  NAMES SDL2.lib
  HINTS ENV{CMAKE_PREFIX_PATH}
  PATH_SUFFIXES SDL2-2.0.14/lib/x64
)
find_library(SDL2MAIN_LIB
  NAMES SDL2main.lib
  HINTS ENV{CMAKE_PREFIX_PATH}
  PATH_SUFFIXES SDL2-2.0.14/lib/x64
)

find_path(SDL2_INCLUDE_DIR
  NAMES SDL.h
  HINTS ENV{CMAKE_PREFIX_PATH}
  PATH_SUFFIXES SDL2-2.0.14/include
)

find_library(JSON_D_LIB
	NAMES json.lib
	HINTS ENV{CMAKE_PREFIX_PATH}
	PATH_SUFFIXES json/json/lib/debug
)
find_library(JSON_R_LIB
	NAMES json.lib
	HINTS ENV{CMAKE_PREFIX_PATH}
	PATH_SUFFIXES json/json/lib/release
)
find_path(JSON_INCLUDE
	NAMES json.h
	HINTS ENV{CMAKE_PREFIX_PATH}
	PATH_SUFFIXES json/json/include
)

include_directories(${SDL2_INCLUDE_DIR} ${JSON_INCLUDE})
target_link_libraries(paint ${SDL2_LIB} ${SDL2MAIN_LIB} debug ${JSON_D_LIB} optimized ${JSON_R_LIB})
