#include <stdbool.h>
#include "../../libs/MiniAudio/miniaudio.h"



void set_volume_controls_in_percents(ma_sound *audioSound, const short volumePercertange) {
    ma_sound_set_volume(audioSound, volumePercertange / 100.0);
    printf("Dancler Terminal Log: Volume set to %d %%.\n", volumePercertange);
}

void load_audio_to_queue(const char filename[], ma_resource_manager *queue, ma_resource_manager_data_source *dataSource) {
    const ma_result queueResult = ma_resource_manager_data_source_init(queue, filename, 0, NULL, dataSource);
    if (queueResult)
        printf("Dancler Terminal Log: Audio file \"%s\" has been successfully added to queue.\n", filename);
    else
        printf("Dancler Terminal Log: Audio file \"%s\" has failed adding to queue.\n", filename);
}

void unload_audio_from_queue(ma_resource_manager_data_source *dataSource) {
    const ma_result queueResult = ma_resource_manager_data_source_uninit(dataSource);
    if (queueResult)
        printf("Dancler Terminal Log: Audio file has been removed from queue.\n");
    else
        printf("Dancler Terminal Log: Audio file could not be removed from queue.\n"); // TODO: maybe change text bro
}

void toggle_playback(ma_sound *sound) {
    const ma_bool32 isPlaying = ma_sound_is_playing(sound);
    if (isPlaying) {
        ma_sound_stop(sound);
        printf("Dancler Terminal Log: Sound has stopped playing.\n");
    }
    else {
        ma_sound_start(sound);
        printf("Dancler Terminal Log: Sound has started playing.\n");
    }
}

void toggle_loop(ma_sound *sound) {
    const ma_bool32 isLoop = ma_sound_is_looping(sound);
    ma_sound_set_looping(sound, isLoop);
    const char loopSwitch[] = isLoop ? "on" : "off";
    printf("Dancler Terminal Log: Looping is %s.\n", loopSwitch);
}