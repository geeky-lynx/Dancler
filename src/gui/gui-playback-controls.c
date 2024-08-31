#include "../header.h"
#include "../audio-controls/sound-controls.h"



size_t playlistIndex = 0;
size_t playlistSize = 3;
const char *playlist[] = {"FH.mp3", "ShesHomeless.mp3", "BG-HS.mp3"};


void play_stop_current_audio() {
    const int RESULT = is_audio_loaded();
    if (!RESULT) {
        load_audio_to_queue(playlist[playlistIndex]);
    }
    toggle_playback();
}

void start_previous_audio(void) {
    load_audio_to_queue(playlist[(--playlistIndex) % playlistSize]);
    toggle_playback();
}

void start_next_audio(void) {
    load_audio_to_queue(playlist[(++playlistIndex) % playlistSize]);
    toggle_playback();
}

inline void mute_audio(void) {
    toggle_volume();
}
