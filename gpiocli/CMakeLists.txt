# RPI-GPIO/gpiocli
cmake_minimum_required(VERSION 3.20)

file(MAKE_DIRECTORY "rsc")
include(VersionTag)
MAKE_VERSION_HEADER("${CMAKE_CURRENT_SOURCE_DIR}/rsc/version.h" "gpiocli" "${RPI_GPIO_VERSION}")

file(GLOB SRCS
	RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
	CONFIGURE_DEPENDS
	"*.c*"
)
file(GLOB HEADERS
	RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
	CONFIGURE_DEPENDS
	"*.h*"
)

add_executable(gpiocli "${SRCS}" "rsc/version.h")

set_property(TARGET gpiocli PROPERTY CXX_STANDARD 20)
set_property(TARGET gpiocli PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET gpiocli PROPERTY POSITION_INDEPENDENT_CODE ON)

target_sources(gpiocli PRIVATE "${HEADERS}")

target_link_libraries(gpiocli PRIVATE gpiolib TermAPI optlib)
