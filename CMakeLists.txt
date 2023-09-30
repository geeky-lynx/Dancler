cmake_minimum_required(VERSION 3.13)
project(dancler C)

find_package(PkgConfig REQUIRED)
find_package(GTK REQUIRED)

pkg_check_modules(GTK REQUIRED gtk4)
# pkg_check_modules(PORTAUDIO REQUIRED portaudio-2.0)

add_executable(
	dancler
	src/main.c
)

# For MacOS, Linux and BSD

target_link_libraries(dancler
	PRIVATE dl
)

target_link_libraries(dancler
	PRIVATE pthread
)

target_link_libraries(dancler
	PRIVATE m
)

 # Including GTK library

target_link_libraries(dancler
	PRIVATE ${GTK_LIBRARIES}
)

target_include_directories(dancler
	PRIVATE ${GTK_INCLUDE_DIRS}
)

target_link_directories(dancler
	PRIVATE ${GTK_LIBRARY_DIRS}
)