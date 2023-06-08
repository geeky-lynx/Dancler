#include <gtk/gtk.h>

// #include "gui-playback-information.c"
// #include "gui-playback-controls.c"

static void initialize_window_layout(GtkApplication *application, gpointer userData) {
    GtkWidget   *mainWindow,
                *mainBox,

                *infoBox,
                *controlBox,
                *playlistBox,

                *audioInfosBox,
                *audioTitleLabel,
                *audioAuthorLabel,
                *audioCoverImageBox,

                *audioLengthLabel,
                *audioCurrentTimeLabel,
                *audioCurrentPlaybackProgressbar,
                *playStopButton,
                *nextButton,
                *previousButton,
                *shuffleButton,
                *loopPlaylistButton,
                *volumeToggleButton,
                *effectsControlButton,

                *playlistGrid;

    mainWindow = gtk_application_new_window(application);
    gtk_window_set_title(GTK_WINDOW(mainWindow), "Dancler");
    gtk_window_set_default_size(GTK_WINDOW(mainWindow), 600, 400);

    mainBox = gtk_new_box(GTK_ORIENTATION_VERTICAL, 0);
    gtk_window_set_child(GTK_WINDOW(mainWindow), mainBox);



    infoBox = gtk_new_box(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_halign(infoBox, GTK_ALIGN_START);
    gtk_widget_set_valign(infoBox, GTK_ALIGN_START);

    audioCoverImageBox = gtk_new_box(GTK_ORIENTATION_VERTICAL, 0);

    audioInfosBox = gtk_new_box(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(infoBox, GTK_ALIGN_START);
    gtk_widget_set_valign(infoBox, GTK_ALIGN_START);

    audioTitleLabel = gtk_label_new("Fearless Hero");
    audioAuthorLabel = gtk_label_new("Unknown authors");

    gtk_box_append(GTK_BOX(audioInfosBox), audioTitleLabel);
    gtk_box_append(GTK_BOX(audioInfosBox), audioAuthorLabel);

    gtk_box_append(GTK_BOX(infoBox), audioCoverImageBox);
    gtk_box_append(GTK_BOX(infoBox), audioInfosBox);


    gtk_box_append(GTK_BOX(mainBox), infoBox);
}