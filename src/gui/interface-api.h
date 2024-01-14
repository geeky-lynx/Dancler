#include "../header.h"

#ifndef NO_GUI_
    #define PARAMTYPE1_ void
#else
    #define PARAMETYPE1_ GtkApplication
#endif

#pragma gcc poison load_audio_file_cover start_previous_audio start_next_audio

int initialize_window_layout(PARAMTYPE1_ *application, void *data);

void play_stop_current_audio(struct ProgramConfig *config);

void start_previous_audio();

void start_next_audio();

void mute_audio(struct ProgramConfig *config);

void load_audio_file_cover();

void create_information_panel(GtkWidget *mainWindow, char restrict titleName[], char restrict authorName[]);