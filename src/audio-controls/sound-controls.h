#include "../header.h"

void set_volume_in_percents(ma_sound *audioSound, const short volumePercertange);

int load_audio_to_queue(const char filename[], ma_resource_manager *queue, ma_resource_manager_data_source *dataSource, ma_sound *sound, ma_engine *engine);

int unload_audio_from_queue(ma_resource_manager_data_source *dataSource, ma_sound *sound);

int toggle_playback(ma_sound *sound);

void toggle_loop(ma_sound *sound);

void toggle_volume(ma_sound *sound);