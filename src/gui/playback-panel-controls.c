#include "../header.h"
#include "gui-controls.h"
#include "playback-panel.h"
#include "../audio-controls/sound-controls.h"



static size_t playlistIndex = 0;
static size_t playlistSize = 3;
const char *playlist[] = {"FH.mp3", "ShesHomeless.mp3", "BG-HS.mp3"};



void play_stop_current_audio() {
    const int RESULT = is_audio_loaded();
    if (!RESULT) {
        load_audio_to_queue(playlist[playlistIndex]);
    }
    toggle_playback();
    gtk_label_set_text(GTK_LABEL(get_title_label()), playlist[playlistIndex]);
}



void start_previous_audio() {
    const int RESULT = is_audio_loaded();
    if (RESULT) {
        stop_playback();
        unload_audio_from_queue();
    }

    playlistIndex = (playlistIndex - 1) % playlistSize;

    load_audio_to_queue(playlist[playlistIndex]);
    start_playback();
    gtk_label_set_text(GTK_LABEL(get_title_label()), playlist[playlistIndex]);
}



void start_next_audio() {
    const int RESULT = is_audio_loaded();
    if (RESULT) {
        stop_playback();
        unload_audio_from_queue();
    }

    playlistIndex = (playlistIndex + 1) % playlistSize;

    load_audio_to_queue(playlist[playlistIndex]);
    start_playback();
    gtk_label_set_text(GTK_LABEL(get_title_label()), playlist[playlistIndex]);
}



extern inline void mute_audio(void) {
    toggle_volume();
}



void change_volume(GtkAdjustment *volumeAdjustment, void *data) {
    // DEBUG_ASSERT_(VOLUME_ADJUSTMENT_SRC != nullptr, "Passed GtkAdjustment* Volume is NULL");

    const float WHOLE_PERCENTAGE = (float)gtk_adjustment_get_value(volumeAdjustment);
    set_volume_in_percents(WHOLE_PERCENTAGE);
    (void)data; // Ignore unused parameter warning
}
