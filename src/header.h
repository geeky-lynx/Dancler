#ifndef DANCLER_HEADER_
#define DANCLER_HEADER_ 1

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>

#ifdef PRODUCTION_
    #define DEBUG_ASSERT_(x) /* No runtime check */
    /* In case `static_assert` causes some symbol errors */
    #ifndef static_assert
        #define static_assert(x, msg)
    #endif
#else
    #include <assert.h>
    #define MA_DEBUG_OUTPUT
    #define DEBUG_ASSERT_(x) assert(x)
#endif


#define MA_NO_NULL
#define MA_ENABLE_ONLY_SPECIFIC_BACKENDS
#if defined(_WIN32)
    #define MA_ENABLE_WASAPI
    #define MA_ENABLE_DSOUND
    #define MA_ENABLE_WINMM
#elif defined(__linux__)
    #define MA_ENABLE_PULSEAUDIO
    #define MA_ENABLE_ALSA
    #define MA_ENABLE_JACK
#elif defined(__APPLE__)
    #define MA_ENABLE_COREAUDIO
#elif defined(__DragonFly__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
    #define MA_ENABLE_OSS
    #define MA_ENABLE_SNDIO
    #define MA_ENABLE_AUDIO4
#endif

// TODO: Check if this works, or needs more focus
// If Apple is bitching, this one might be for you
#ifdef __APPLE__
    #define MA_NO_RUNTIME_LINKING
#endif

#include "../libs/MiniAudio/miniaudio.h"

#include <gtk/gtk.h>

#endif /* DANCLER_HEADER_ */
