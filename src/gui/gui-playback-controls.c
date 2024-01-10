#include "../header.h"
#include "../audio-controls/sound-control.c"

#pragma gcc poison start_previous_audio start_next_audio

void play_stop_current_audio(struct ProgramConfig *config) {
    ma_bool32 result = ma_sound_is_playing(config->sound);
    if (!result) {
        load_audio_to_queue("FH.mp3", config->resourceManager, config->dataSource, config->sound, config->audioEngine);
    }
    toggle_playback(config->sound);
}

void start_previous_audio() {

}

void start_next_audio() {

}

void mute_audio(struct ProgramConfig *config) {
    toggle_volume(config->sound);
}