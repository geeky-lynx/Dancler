#define MINIAUDIO_IMPLEMENTATION
#include "../header.h"
// Separate Miniaudio function definitions
// from Dancler's source files.

// Reason: Speeding up new building tasks
// with CMake, allowing faster times
// when modifying source files
// (specifically `sound-control.c`)

// Note: first time compilations,
// changes to `CMakeLists.txt`, fresh
// rebuildings (cleaning up `./build/*`
// or putting some CMAKE/GCC/Clang flags
// and compiling again) and updating
// Miniaudio header will make building
// process with CMake slower due to this
// file
