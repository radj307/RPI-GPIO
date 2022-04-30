# RPI-GPIO/lib
cmake_minimum_required(VERSION 3.20)

# Glob code files:
file(GLOB SRCS
	RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
	CONFIGURE_DEPENDS
	"src/*.c*"
)
file(GLOB HEADERS
	RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
	CONFIGURE_DEPENDS
	"include/*.h*"
)

# Create a library
add_library(gpiolib STATIC "${SRCS}")

set_property(TARGET gpiolib PROPERTY POSITION_INDEPENDENT_CODE ON)

target_include_directories(gpiolib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

# add headers:
target_sources(gpiolib PRIVATE "${HEADERS}")

target_link_libraries(gpiolib PRIVATE shared)
