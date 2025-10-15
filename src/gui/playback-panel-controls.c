#include "../header.h"
#include "gui-controls.h"
#include "playback-panel.h"
#include "../audio-controls/sound-controls.h"
#include "../database/playlist.h"



// static size_t playlistIndex = 0;
// static size_t playlistSize = 3;
// const char *playlist[] = {"FH.mp3", "ShesHomeless.mp3", "BG-HS.mp3"};



void play_stop_current_audio() {
    const int RESULT = is_audio_loaded();
    if (!RESULT)
        load_audio_to_queue(get_current_item().filepath);

    toggle_playback();
    GtkButton* button = GTK_BUTTON(get_play_stop_button());
    gtk_label_set_text(GTK_LABEL(get_title_label()), get_current_item().filepath);
    if (is_audio_playing())
        gtk_button_set_icon_name(button, "media-playback-pause");
    else
        gtk_button_set_icon_name(button, "media-playback-start");
}



void start_previous_audio() {
    const int RESULT = is_audio_loaded();
    if (RESULT) {
        stop_playback();
        unload_audio_from_queue();
    }

    // playlistIndex = (playlistIndex - 1) % playlistSize;

    // load_audio_to_queue(playlist[playlistIndex]);
    playlist_go_previous();
    load_audio_to_queue(get_current_item().filepath);
    start_playback();
    gtk_label_set_text(GTK_LABEL(get_title_label()), get_current_item().filepath);
    gtk_button_set_icon_name(GTK_BUTTON(get_play_stop_button()), "media-playback-start");
}



void start_next_audio() {
    const int RESULT = is_audio_loaded();
    if (RESULT) {
        stop_playback();
        unload_audio_from_queue();
    }

    // playlistIndex = (playlistIndex + 1) % playlistSize;

    // load_audio_to_queue(playlist[playlistIndex]);
    playlist_go_next();
    load_audio_to_queue(get_current_item().filepath);
    start_playback();
    gtk_label_set_text(GTK_LABEL(get_title_label()), get_current_item().filepath);
    gtk_button_set_icon_name(GTK_BUTTON(get_play_stop_button()), "media-playback-start");
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
