#ifndef DANCLER_INTERFACE_API_
#define DANCLER_INTERFACE_API_ 1

#include "../header.h"

#include <gtk/gtk.h>

/*
    void initialize_window_layout(GtkApplication *application, gpointer userData): Creates user GUI
    Parameters:
        1. `GtkApplication *application`
        2. `gpointer userData` (a.k.a. `void*`)
    Returns: Nothing
    Note: This function is only used once as a callback
*/
void initialize_window_layout(GtkApplication *application, gpointer userData);

/*
    void create_playback_ui(GtkWidget *windowBox): Forms playback information & controls GUI elements
    Parameters:
        1. GtkWidget *windowBox
            - GTK box (which is the "root" box) to append to
    Returns: Nothing
*/
void create_playback_ui(GtkWidget *windowBox);

/*
    void create_playlist_ui(GtkWidget *windowBox): Forms playlist (list of songs) table GUI elements
    Parameters:
        1. GtkWidget *windowBox
            - GTK box (which is the "root" box) to append to
    Returns: Nothing
*/
void create_playlist_ui(GtkWidget *windowBox);

#endif
