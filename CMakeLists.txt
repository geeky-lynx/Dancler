cmake_minimum_required(VERSION 3.13)
project(dancler C)

# set(CMAKE_CXX_COMPILER "gcc")
set(CMAKE_C_STANDARD 23)
add_compile_options(-Wall)
add_compile_options(-Wextra)
if (PRODUCTION_)
    add_compile_options(-O3) # Optimization in production
else (PRODUCTION_)
    set(CMAKE_CXX_FLAGS_DEBUG_INIT "-fstack-protector")
    add_compile_options(-g)
    add_compile_options(-Og) # Optimization in debug mode
endif (PRODUCTION_)

find_package(PkgConfig REQUIRED)
find_package(GTK REQUIRED)

pkg_check_modules(GTK REQUIRED gtk4)

add_executable(
	dancler
	src/types/german-string.c
	src/audio-controls/miniaudio-definitions.c
	src/audio-controls/sound-control.c
	src/gui/playback-panel-controls.c
	src/gui/playback-panel.c
	src/gui/playlist-panel.c
	src/gui/main-window.c
	src/main.c
)


# For MacOS, Linux and BSD
if (UNIX)
    target_link_libraries(dancler
    	PRIVATE dl pthread m
    )

    # Linking -latomic for 32-bit ARM processors
    if (_M_ARM32)
        target_link_libraries(dancler
            PRIVATE atomic
        )
    endif (_M_ARM32)

endif (UNIX)


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
