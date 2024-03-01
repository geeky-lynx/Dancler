#include "../header.h"

#ifndef DANCLER_SOUND_CONTROLS_
#define DANCLER_SOUND_CONTROLS_ 1

int initialize_backend(void);

int unitialize_backend(void);

void set_volume_in_percents(const short volumePercertange);

int load_audio_to_queue(const char filename[]);

int unload_audio_from_queue(void);

int toggle_playback(void);

void toggle_loop(void);

void toggle_volume(void);

int is_audio_loaded(void);

#endif