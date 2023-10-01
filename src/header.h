#ifndef DANCLER_HEADER_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>

#define MINIAUDIO_IMPLEMENTATION
#define MA_NO_NULL
#define MA_DEBUG_OUTPUT
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
#include "../libs/MiniAudio/miniaudio.h"

#include <gtk/gtk.h>

// #include "./audio-controls/sound-control.c"

// #include "./gui/gui-playback-controls.c"
// #include "./gui/gui-playback-information.c"


#define DANCLER_HEADER_
#endif