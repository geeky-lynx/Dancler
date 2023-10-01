#include "header.h"
#include "./gui/gui-main-window.c"

int main(int argc, char *argv[]) {
    int status;
    ma_result result;
    ma_engine engine;
    ma_sound sound;
    GtkApplication *userInterface;

    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        perror("Failed to initialize audio engine.\n");
        return 2;
    }

    userInterface = gtk_application_new("com.github.heroes_of_balkan.dancler", G_APPLICATION_REPLACE);
    g_signal_connect(userInterface, "activate", G_CALLBACK(initialize_window_layout), NULL);
    status = g_application_run(G_APPLICATION(userInterface), argc, argv);
    g_object_unref(userInterface);


    ma_engine_uninit(&engine);
    
    return 0;
}