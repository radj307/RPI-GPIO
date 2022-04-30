# RPI-GPIO/
cmake_minimum_required(VERSION 3.20)

if (MSVC)
	message(FATAL_ERROR "This project cannot be compiled on Windows!")
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/307lib/307modules")

set(ENV{RPI_GPIO_VERSION} "0.0.0")

include(VersionTag)

GET_VERSION_TAG("${CMAKE_CURRENT_SOURCE_DIR}" "RPI_GPIO")

project("RPI_GPIO" VERSION "${RPI_GPIO_VERSION}" LANGUAGES CXX)

add_subdirectory("307lib")
add_subdirectory("lib")
add_subdirectory("test")
