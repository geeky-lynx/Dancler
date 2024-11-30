#include "../header.h"

static bool isLoaded = false;
static bool isSoundInited = false;

static float oldVolumePercentage = 0.0f;

static ma_sound sound;
static ma_engine engine;
static ma_resource_manager resourceManager;
static ma_resource_manager_config resourceManagerConfig;
static ma_resource_manager_data_source dataSource;



int initialize_backend(void) {
    ma_result result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        // perror("Failed to initialize audio engine.\n");
        return result;
    }

    resourceManagerConfig = ma_resource_manager_config_init();
    result = ma_resource_manager_init(&resourceManagerConfig, &resourceManager);
    if (result != MA_SUCCESS) {
        // perror("Failed to initialize resource manager.\n");
        return result;
    }
    return 0;
}



int unitialize_backend(void) {
    ma_resource_manager_uninit(&resourceManager);
    ma_engine_uninit(&engine);
    if (isSoundInited)
        ma_sound_uninit(&sound);
    ma_data_source_uninit(&dataSource);
    return 0;
}



void set_volume_in_percents(float volumePercertange) {
    ma_sound_set_volume(&sound, volumePercertange / 100.0f);
}



int load_audio_to_queue(const char filename[]) {
    // printf("1\n");
    // const ma_result QUEUE_RESULT = ma_resource_manager_data_source_init(queue, filename, 0, NULL, dataSource);
    // if (QUEUE_RESULT == MA_SUCCESS)
    //     isLoaded = true;

    // printf("2\n");
    // ma_sound_init_from_data_source(engine, dataSource, 0, NULL, sound);
    const ma_result SOUND_RESULT = ma_sound_init_from_file(&engine, filename, 0, NULL, NULL, &sound);
    if (SOUND_RESULT != MA_SUCCESS)
        return 0;

    isSoundInited = true;
    // printf("3\n");
    // if (queueResult)
        // printf("Dancler Terminal Log: Audio file \"%s\" has been successfully added to queue.\n", filename);
    // else
    //     printf("Dancler Terminal Log: Audio file \"%s\" has failed adding to queue.\n", filename);
    // return (const int)QUEUE_RESULT;
    return 0;
}



int unload_audio_from_queue(void) {
    ma_sound_uninit(&sound);
    // const ma_result QUEUE_RESULT = ma_resource_manager_data_source_uninit(&dataSource);
    const int QUEUE_RESULT = MA_SUCCESS; // since resource manager isn't yet in use...
    // if (queueResult)
    //     printf("Dancler Terminal Log: Audio file has been removed from queue.\n");
    // else
    //     printf("Dancler Terminal Log: Audio file could not be removed from queue.\n"); // TODO: maybe change text bro
    isSoundInited = false;
    return QUEUE_RESULT;
}



int toggle_playback(void) {
    // printf("isLoaded: %d\n", isLoaded);
    if (isLoaded)
        return -1;

    const ma_bool32 IS_PLAYING = ma_sound_is_playing(&sound);
    // printf("IS_PLAYING: %d\n", IS_PLAYING);
    if (IS_PLAYING) {
        // printf("da\n");
        return ma_sound_stop(&sound);
        // printf("Dancler Terminal Log: Sound has stopped playing.\n");
    }
    else {
        // printf("ne\n");
        return ma_sound_start(&sound);
        // printf("Dancler Terminal Log: Sound has started playing.\n");
    }
    return IS_PLAYING;
}



void toggle_loop(void) {
    const ma_bool32 IS_LOOPING = ma_sound_is_looping(&sound);
    ma_sound_set_looping(&sound, !IS_LOOPING);
    // if (IS_LOOPING)
    //     printf("Dancler Terminal Log: Looping is on.\n");
    // else
    //     printf("Dancler Terminal Log: Looping is on.\n");
}



void toggle_volume(void) {
    const float currentVolume = ma_sound_get_volume(&sound);
    ma_sound_set_volume(&sound, oldVolumePercentage);
    oldVolumePercentage = currentVolume;
}



extern inline int is_audio_loaded(void) {
    return isSoundInited;
}
