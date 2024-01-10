#include "../header.h"

static bool isLoaded = false;
static bool isSoundInited = false;



void set_volume_controls_in_percents(ma_sound *audioSound, const short volumePercertange) {
    ma_sound_set_volume(audioSound, volumePercertange / 100.0f);
    // printf("Dancler Terminal Log: Volume set to %d %%.\n", volumePercertange);
}

int load_audio_to_queue(const char filename[], ma_resource_manager *queue, ma_resource_manager_data_source *dataSource, ma_sound *sound, ma_engine *engine) {
    printf("1\n");
    // const ma_result QUEUE_RESULT = ma_resource_manager_data_source_init(queue, filename, 0, NULL, dataSource);
    // if (QUEUE_RESULT == MA_SUCCESS)
    //     isLoaded = true;
    
    printf("2\n");
    const ma_result SOUND_RESULT = ma_sound_init_from_file(engine, filename, 0, NULL, NULL, sound);// ma_sound_init_from_data_source(engine, dataSource, 0, NULL, sound);
    if (SOUND_RESULT == MA_SUCCESS)
        isSoundInited = true;
    // if (queueResult)
    //     printf("Dancler Terminal Log: Audio file \"%s\" has been successfully added to queue.\n", filename);
    // else
    //     printf("Dancler Terminal Log: Audio file \"%s\" has failed adding to queue.\n", filename);
    // return (const int)QUEUE_RESULT;
    return 0;
}

int unload_audio_from_queue(ma_resource_manager_data_source *dataSource, ma_sound *sound) {
    ma_sound_uninit(sound);
    const ma_result QUEUE_RESULT = ma_resource_manager_data_source_uninit(dataSource);
    // if (queueResult)
    //     printf("Dancler Terminal Log: Audio file has been removed from queue.\n");
    // else
    //     printf("Dancler Terminal Log: Audio file could not be removed from queue.\n"); // TODO: maybe change text bro
    return QUEUE_RESULT;
}

int toggle_playback(ma_sound *sound) {
    if (isLoaded)
        return -1;

    const ma_bool32 IS_PLAYING = ma_sound_is_playing(sound);
    if (IS_PLAYING) {
        return ma_sound_stop(sound);
        // printf("Dancler Terminal Log: Sound has stopped playing.\n");
    }
    else {
        return ma_sound_start(sound);
        // printf("Dancler Terminal Log: Sound has started playing.\n");
    }
    return IS_PLAYING;
}

void toggle_loop(ma_sound *sound) {
    const ma_bool32 IS_LOOPING = ma_sound_is_looping(sound);
    ma_sound_set_looping(sound, !IS_LOOPING);
    // if (IS_LOOPING)
    //     printf("Dancler Terminal Log: Looping is on.\n");
    // else
    //     printf("Dancler Terminal Log: Looping is on.\n");
}

void toggle_volume(ma_sound *sound) {
    const float currentVolume = ma_sound_get_volume(sound);
    // static float initialVolume = currentVolume;
    if (currentVolume == 0) {
        ma_sound_set_volume(sound, currentVolume / 100.0);
        // ma_sound_set_volume(sound, initialVolume / 100.0);
        // printf("Dancler Terminal Log: Current playback is unmuted.\n");
    }
    else {
        ma_sound_set_volume(sound, 0.0);
        // printf("Dancler Terminal Log: Current playback is muted.\n");
    }
}