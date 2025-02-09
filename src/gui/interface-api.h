#ifndef DANCLER_INTERFACE_API_
#define DANCLER_INTERFACE_API_ 1

#include "../header.h"

void initialize_window_layout(GtkApplication *application, gpointer userData);

void initialize_ui_values(); // Initialized all required values

void create_playback_ui(GtkWidget *windowBox); // Forms information & controls for current playback

void create_playlist_ui(GtkWidget *windowBox); // Forms playlist table (list of songs)

#endif
