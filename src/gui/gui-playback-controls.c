#include "../header.h"
#include "../audio-controls/sound-controls.h"



bool isPlaying = false;
size_t playlistIndex = 0;
size_t playlistSize = 3;
const char *playlist[] = {"FH.mp3", "ShesHomeless.mp3", "BG-HS.mp3"};



void play_stop_current_audio(void) {
    const int RESULT = is_audio_loaded();
    if (!RESULT) {
        load_audio_to_queue(playlist[playlistIndex]);
    }
    toggle_playback();
    isPlaying = !isPlaying;
}



void start_previous_audio(void) {
    const int RESULT = is_audio_loaded();
    if (RESULT) {
        toggle_playback();
        unload_audio_from_queue();
    }
    load_audio_to_queue(playlist[(--playlistIndex) % playlistSize]);
    toggle_playback();
}



void start_next_audio(void) {
    const int RESULT = is_audio_loaded();
    if (RESULT) {
        toggle_playback();
        unload_audio_from_queue();
    }
    load_audio_to_queue(playlist[(++playlistIndex) % playlistSize]);
    toggle_playback();
}



extern inline void mute_audio(void) {
    toggle_volume();
}
