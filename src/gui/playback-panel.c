#include "./gui-controls.h"
#include "./interface-api.h"
#include "./playback-panel.h"

#define DEFAULT_COVER_IMAGE_ "assets/no-cover.png"
#define DEFAULT_TITLE_NO_PLAYBACK_ "No playback"
#define DEFAULT_TITLE_NO_TITLE_ "Unknown title"
#define DEFAULT_AUTHORS_ "Unknown authors"
#define DEFAULT_ZERO_TIMER_ "0:00"


static GtkAdjustment *playbackTime; // To be used for time slider
static GtkAdjustment *playbackVolume; // To be used for volume slider


GtkWidget *titleLabel = NULL;
GtkWidget *authorsLabel = NULL;

GtkWidget *playStopButton = NULL;
GtkWidget *nextButton = NULL;
GtkWidget *previousButton = NULL;



void create_playback_ui(GtkWidget *windowBox) {
    GtkWidget   *playbackBox = NULL,

                *infoAndControlBox = NULL,
                *infoBox = NULL,
                *coverBox = NULL,
                *coverImage = NULL,

                *controlsBox = NULL,
                *timeBox = NULL,
                *currentTimeLabel = NULL,
                *totalTimeLabel = NULL,
                *timeSlider = NULL,

                *actionsBox = NULL,
                *volumeSlider = NULL;

    playbackTime = gtk_adjustment_new(0.0, 0.0, 10.0, 1.0, 1.0, 1.0);
    playbackVolume = gtk_adjustment_new(100.0, 0.0, 100.0, 1.0, 1.0, 1.0);


    playbackBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_halign(playbackBox, GTK_ALIGN_START);
    gtk_widget_set_valign(playbackBox, GTK_ALIGN_START);


    /* Creating audio cover GUI elements */
    coverBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_halign(coverBox, GTK_ALIGN_START);
    gtk_widget_set_valign(coverBox, GTK_ALIGN_START);

    coverImage = gtk_image_new();
    gtk_image_set_from_file(GTK_IMAGE(coverImage), DEFAULT_COVER_IMAGE_);
    gtk_widget_set_size_request(GTK_WIDGET(coverImage), 200, 200);


    /* Creating audio playback information GUI elements (duh) */
    infoAndControlBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(infoAndControlBox, GTK_ALIGN_START);
    gtk_widget_set_valign(infoAndControlBox, GTK_ALIGN_START);

    infoBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(infoBox, GTK_ALIGN_START);
    gtk_widget_set_valign(infoBox, GTK_ALIGN_START);

    titleLabel = gtk_label_new(DEFAULT_TITLE_NO_PLAYBACK_);
    authorsLabel = gtk_label_new(DEFAULT_AUTHORS_);
    gtk_widget_set_hexpand(GTK_WIDGET(authorsLabel), true);


    /* Creating time stuff GUI elements */
    controlsBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(controlsBox, GTK_ALIGN_START);
    gtk_widget_set_valign(controlsBox, GTK_ALIGN_START);

    timeBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_halign(timeBox, GTK_ALIGN_START);
    gtk_widget_set_valign(timeBox, GTK_ALIGN_START);
    gtk_widget_set_hexpand(timeBox, true);

    currentTimeLabel = gtk_label_new(DEFAULT_ZERO_TIMER_);
    totalTimeLabel = gtk_label_new(DEFAULT_ZERO_TIMER_);
    timeSlider = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, playbackTime);
    gtk_widget_set_size_request(timeSlider, 500, -1);


    /* Creating playback control GUI elements */
    actionsBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_halign(actionsBox, GTK_ALIGN_START);
    gtk_widget_set_valign(actionsBox, GTK_ALIGN_START);


    playStopButton = gtk_button_new_from_icon_name("media-playback-start");
    previousButton = gtk_button_new_from_icon_name("media-skip-backward");
    nextButton = gtk_button_new_from_icon_name("media-skip-forward");
    volumeSlider = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, playbackVolume);
    gtk_widget_set_size_request(volumeSlider, 150, -1);
    g_signal_connect_swapped(G_OBJECT(playStopButton), "clicked", G_CALLBACK(play_stop_current_audio), nullptr);
    g_signal_connect_swapped(G_OBJECT(previousButton), "clicked", G_CALLBACK(start_previous_audio), nullptr);
    g_signal_connect_swapped(G_OBJECT(nextButton), "clicked", G_CALLBACK(start_next_audio), nullptr);
    g_signal_connect(G_OBJECT(playbackVolume), "value-changed", G_CALLBACK(change_volume), NULL);


    /* Put everything on the window */
    gtk_box_append(GTK_BOX(coverBox), coverImage);
    gtk_box_append(GTK_BOX(playbackBox), coverBox);

    gtk_box_append(GTK_BOX(infoBox), titleLabel);
    gtk_box_append(GTK_BOX(infoBox), authorsLabel);

    gtk_box_append(GTK_BOX(infoAndControlBox), infoBox);

    gtk_box_append(GTK_BOX(timeBox), currentTimeLabel);
    gtk_box_append(GTK_BOX(timeBox), timeSlider);
    gtk_box_append(GTK_BOX(timeBox), totalTimeLabel);

    gtk_box_append(GTK_BOX(controlsBox), timeBox);

    gtk_box_append(GTK_BOX(actionsBox), previousButton);
    gtk_box_append(GTK_BOX(actionsBox), playStopButton);
    gtk_box_append(GTK_BOX(actionsBox), nextButton);
    gtk_box_append(GTK_BOX(actionsBox), volumeSlider);

    gtk_box_append(GTK_BOX(controlsBox), actionsBox);

    gtk_box_append(GTK_BOX(infoAndControlBox), controlsBox);

    gtk_box_append(GTK_BOX(playbackBox), infoAndControlBox);

    gtk_box_append(GTK_BOX(windowBox), playbackBox);
}




GtkWidget *get_title_label() {
  return titleLabel;
}



GtkWidget *get_authors_label() {
  return authorsLabel;
}



GtkWidget *get_play_stop_button() {
  return playStopButton;
}



GtkWidget *get_next_song_button() {
  return nextButton;
}



GtkWidget *get_previous_song_button() {
  return previousButton;
}
