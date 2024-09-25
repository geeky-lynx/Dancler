cmake_minimum_required(VERSION 3.13)
project(dancler C)

# set(CMAKE_CXX_COMPILER "gcc")
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-fstack-protector")
add_compile_options(-g)
add_compile_options(-Wall)
add_compile_options(-Wextra)
add_compile_options(-Og) # Optimization in debug mode

find_package(PkgConfig REQUIRED)
find_package(GTK REQUIRED)

pkg_check_modules(GTK REQUIRED gtk4)
# pkg_check_modules(PORTAUDIO REQUIRED portaudio-2.0)

add_executable(
	dancler
	src/audio-controls/sound-control.c
	src/gui/gui-playback-controls.c
	src/gui/gui-main-window.c
	src/main.c
)


# For MacOS, Linux and BSD
# if(defined(unix))
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
