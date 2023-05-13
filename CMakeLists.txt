project(dancler C)
cmake_minimum_required(VERSION 3.13)

find_package(PkgConfig REQUIRED)

# pkg_check_modules(PORTAUDIO REQUIRED portaudio-2.0)

add_executable(
	dancler
	src/main.c
)

# For Linux

target_link_libraries(dancler
	PRIVATE dl
)

target_link_libraries(dancler
	PRIVATE pthread
)

target_link_libraries(dancler
	PRIVATE m
)

# target_link_libraries(dancler
# 	"${PORTAUDIO_LIBRARIES}"
# )

# target_include_directories(dancler
# 	"${PORTAUDIO_INCLUDE_DIRS}"
# )

# target_link_directories(dancler
# 	"${PORTAUDIO_LIBRARY_DIRS}"
# )

