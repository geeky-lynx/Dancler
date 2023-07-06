#include <gtk/gtk.h>

// #include "gui-playback-information.c"
// #include "gui-playback-controls.c"

static void initialize_window_layout(GtkApplication *application, gpointer userData) {
    GtkWidget   *mainWindow,
                *mainBox,

                *playbackBox,
                *playlistBox,

                *playbackLeftBox,
                *playbackRightBox,
                *infoBox,
                *titleLabel,
                *authorsLabel,
                *coverBox,
                *coverImage,

                *controlsBox,
                *timeBox,
                *currentTimeLabel,
                *totalTimeLabel,
                *timeSlider,

                *actionsBox,
                *playStopButton,
                *nextButton,
                *previousButton,
                *muteButton,
                *volumeSlider,

                *sidebar,
                *playlistStack,
                *playlistTable;



    mainWindow = gtk_application_window_new(application);
    gtk_window_set_title(GTK_WINDOW(mainWindow), "Dancler");
    gtk_window_set_default_size(GTK_WINDOW(mainWindow), 600, 400);

    mainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_window_set_child(GTK_WINDOW(mainWindow), mainBox);



    playbackBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_halign(playbackBox, GTK_ALIGN_START);
    gtk_widget_set_valign(playbackBox, GTK_ALIGN_START);


    playbackLeftBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_halign(playbackLeftBox, GTK_ALIGN_START);
    gtk_widget_set_valign(playbackLeftBox, GTK_ALIGN_START);

    coverBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(coverBox, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(coverBox, GTK_ALIGN_CENTER);

    coverImage = gtk_image_new();
    gtk_image_set_from_file(GTK_IMAGE(coverImage), "../assets/no-cover.png");


    playbackRightBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(playbackRightBox, GTK_ALIGN_START);
    gtk_widget_set_valign(playbackRightBox, GTK_ALIGN_START);

    infoBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(infoBox, GTK_ALIGN_START);
    gtk_widget_set_valign(infoBox, GTK_ALIGN_START);

    titleLabel = gtk_label_new("Fearless Hero");
    authorsLabel = gtk_label_new("Unknown authors");


    controlsBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(controlsBox, GTK_ALIGN_START);
    gtk_widget_set_valign(controlsBox, GTK_ALIGN_START);

    timeBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_halign(timeBox, GTK_ALIGN_START);
    gtk_widget_set_valign(timeBox, GTK_ALIGN_START);

    currentTimeLabel = gtk_label_new("0:00");
    totalTimeLabel = gtk_label_new("0:00");
    timeSlider = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, NULL);


    actionsBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_halign(actionsBox, GTK_ALIGN_START);
    gtk_widget_set_valign(actionsBox, GTK_ALIGN_START);

    playStopButton = gtk_button_new_from_icon_name("dancler-play-stop");
    previousButton = gtk_button_new_from_icon_name("dancler-previous");
    nextButton = gtk_button_new_from_icon_name("dancler-next");
    muteButton = gtk_button_new_from_icon_name("dancler-mute");
    volumeSlider = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, NULL);



    playlistBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    sidebar = gtk_stack_sidebar_new();
    playlistStack = gtk_stack_new();
    playlistTable = gtk_tree_view_new();
    gtk_stack_add_child(GTK_STACK(playlistStack), playlistTable);
    gtk_stack_sidebar_set_stack(GTK_STACK_SIDEBAR(sidebar), GTK_STACK(playlistStack));



    gtk_box_append(GTK_BOX(coverBox), coverImage);
    gtk_box_append(GTK_BOX(playbackLeftBox), coverBox);

    gtk_box_append(GTK_BOX(playbackBox), playbackLeftBox);

    gtk_box_append(GTK_BOX(infoBox), titleLabel);
    gtk_box_append(GTK_BOX(infoBox), authorsLabel);

    gtk_box_append(GTK_BOX(playbackRightBox), infoBox);

    gtk_box_append(GTK_BOX(timeBox), currentTimeLabel);
    gtk_box_append(GTK_BOX(timeBox), timeSlider);
    gtk_box_append(GTK_BOX(timeBox), totalTimeLabel);

    gtk_box_append(GTK_BOX(controlsBox), timeBox);

    gtk_box_append(GTK_BOX(actionsBox), previousButton);
    gtk_box_append(GTK_BOX(actionsBox), playStopButton);
    gtk_box_append(GTK_BOX(actionsBox), nextButton);
    gtk_box_append(GTK_BOX(actionsBox), muteButton);
    gtk_box_append(GTK_BOX(actionsBox), volumeSlider);

    gtk_box_append(GTK_BOX(controlsBox), actionsBox);

    gtk_box_append(GTK_BOX(playbackRightBox), controlsBox);

    gtk_box_append(GTK_BOX(playbackBox), playbackRightBox);

    gtk_box_append(GTK_BOX(mainBox), playbackBox);

    gtk_box_append(GTK_BOX(playlistBox), sidebar);



    gtk_window_present(GTK_WINDOW(mainWindow));
}