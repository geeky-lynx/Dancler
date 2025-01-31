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
        ma_sound_uninit(&sound); // Assume end of program; no need to change this variable
    ma_data_source_uninit(&dataSource);
    return 0;
}



void set_volume_in_percents(float volumePercertange) {
    ma_sound_set_volume(&sound, volumePercertange / 100.0f);
}



int load_audio_to_queue(const char filename[]) {
    // const ma_result QUEUE_RESULT = ma_resource_manager_data_source_init(queue, filename, 0, NULL, dataSource);
    // if (QUEUE_RESULT == MA_SUCCESS)
    //     isLoaded = true;

    // ma_sound_init_from_data_source(engine, dataSource, 0, NULL, sound);
    const ma_result SOUND_RESULT = ma_sound_init_from_file(&engine, filename, 0, NULL, NULL, &sound);
    if (SOUND_RESULT != MA_SUCCESS)
        return SOUND_RESULT;

    isSoundInited = true;
    // return (const int)QUEUE_RESULT;
    return 0;
}



int unload_audio_from_queue(void) {
    if (isSoundInited)
        return -1;
    ma_sound_uninit(&sound);
    // const ma_result QUEUE_RESULT = ma_resource_manager_data_source_uninit(&dataSource);
    const int QUEUE_RESULT = MA_SUCCESS; // since resource manager isn't yet in use...
    isSoundInited = false;
    return QUEUE_RESULT;
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



int jump_to_seconds(float seconds) {
    const ma_uint32 SAMPLE_RATE = ma_engine_get_sample_rate(&engine);
    // Implicit conversion from `float` to `unsigned long long`
    const ma_uint64 NEW_CURSOR_POS = SAMPLE_RATE * seconds;
    return ma_sound_seek_to_pcm_frame(&sound, NEW_CURSOR_POS);
}



float retrieve_audio_length_seconds(void) {
    float audioLength = 0;
    const ma_result RESULT = ma_sound_get_length_in_seconds(&sound, &audioLength);
    if (RESULT != MA_SUCCESS)
        return RESULT + 0.0f; // Cast to `float`, in a nicer way
    return audioLength;
}
