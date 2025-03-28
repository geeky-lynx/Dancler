#include "../header.h"
#include "./miniaudio-include.h"

static bool isLoaded = false;
static bool isSoundInited = false;

static float oldVolumePercentage = 0.0f;

static ma_sound sound;
static ma_engine engine;



int initialize_backend(void) {
    return ma_engine_init(NULL, &engine);

}



int unitialize_backend(void) {
    ma_engine_uninit(&engine);
    if (isSoundInited)
        ma_sound_uninit(&sound); // Assume end of program; no need to change this variable
    return 0;
}



void set_volume_in_percents(float volumePercertange) {
    ma_sound_set_volume(&sound, volumePercertange / 100.0f);
}



int load_audio_to_queue(const char filename[]) {
    const ma_result SOUND_RESULT = ma_sound_init_from_file(&engine, filename, 0, NULL, NULL, &sound);
    if (SOUND_RESULT != MA_SUCCESS)
        return SOUND_RESULT;
    isSoundInited = true;
    return 0;
}



int unload_audio_from_queue(void) {
    if (isSoundInited)
        return -1;
    ma_sound_uninit(&sound);
    isSoundInited = false;
    return MA_SUCCESS;
}



int start_playback() {
    if (isLoaded)
        return -1;

    if (!ma_sound_is_playing(&sound))
        return ma_sound_start(&sound);

    return 0;
}



int stop_playback() {
    if (isLoaded)
        return -1;

    if (ma_sound_is_playing(&sound))
        return ma_sound_stop(&sound);

    return 0;
}



int toggle_playback(void) {
    if (isLoaded)
        return -1;

    ma_result playbackResult = -1;

    // TODO: Probably needs better looking code
    const ma_bool32 IS_PLAYING = ma_sound_is_playing(&sound);
    if (IS_PLAYING) {
        playbackResult = ma_sound_stop(&sound);
        if (playbackResult != MA_SUCCESS)
            return -1;
        return IS_PLAYING;
    }

    playbackResult = ma_sound_start(&sound);
    if (playbackResult != MA_SUCCESS)
        return -1;

    return IS_PLAYING;
}



void toggle_loop(void) {
    const ma_bool32 IS_LOOPING = ma_sound_is_looping(&sound);
    ma_sound_set_looping(&sound, !IS_LOOPING);
}



void toggle_volume(void) {
    const float CURRENT_VOLUME = ma_sound_get_volume(&sound);
    ma_sound_set_volume(&sound, oldVolumePercentage);
    oldVolumePercentage = CURRENT_VOLUME;
}



extern inline int is_audio_loaded(void) {
    return isSoundInited;
}



extern inline int is_audio_playing(void) {
    return ma_sound_is_playing(&sound);
}



int jump_to_seconds(float seconds) {
    return ma_sound_seek_to_second(&sound, seconds);
}



float retrieve_audio_length_in_seconds(void) {
    float audioLength = 0;
    const ma_result RESULT = ma_sound_get_length_in_seconds(&sound, &audioLength);
    if (RESULT != MA_SUCCESS)
        return (float)RESULT;
    return audioLength;
}
