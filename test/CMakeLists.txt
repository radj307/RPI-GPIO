# RPI-GPIO/test
cmake_minimum_required(VERSION 3.20)

file(GLOB SRCS
	RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
	CONFIGURE_DEPENDS
	"*.c*"
)

add_executable(gpiotest "${SRCS}")

target_link_libraries(gpiotest PUBLIC shared gpiolib)
