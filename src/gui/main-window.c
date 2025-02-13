#include "../header.h"
#include "./interface-api.h"

void initialize_window_layout(GtkApplication *application, gpointer userData) {
    GtkWidget   *mainWindow = NULL,
                *mainBox = NULL;

    /* Creating base for main window */
    mainWindow = gtk_application_window_new(application);
    gtk_window_set_title(GTK_WINDOW(mainWindow), "Dancler");
    gtk_window_set_default_size(GTK_WINDOW(mainWindow), 600, 400);

    mainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_window_set_child(GTK_WINDOW(mainWindow), mainBox);

    create_playback_ui(mainBox);
    create_playlist_ui(mainBox);

    gtk_window_present(GTK_WINDOW(mainWindow));
}
