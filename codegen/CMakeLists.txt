cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(Codegen LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

if (NOT DEFINED GEODE_HOST_ARM AND APPLE)
	set(CMAKE_OSX_ARCHITECTURES x86_64)
	set(CMAKE_OSX_SYSROOT )
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../include/Geode/utils/fmt codegen_fmt)
add_subdirectory(Broma)

file(GLOB SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

file(GLOB HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/fmt/include/*.h
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(Codegen PUBLIC fmt::fmt Broma)
target_include_directories(Codegen PRIVATE 
	${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_precompile_headers(Codegen PRIVATE 
	${CMAKE_CURRENT_SOURCE_DIR}/src/Shared.hpp
)