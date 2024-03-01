#include "header.h"
#include "./audio-controls/sound-controls.h"
// #define NO_GUI_

// #ifndef NO_GUI_
// #include "./gui/gui-main-window.c"
// #else
// #include "./gui/cli-main-window.c"
// #endif
#include "./gui/interface-api.h"


int main(int argc, char *argv[]) {
    int status;
    GtkApplication *userInterface;
    
    status = initialize_backend();
    if (status != 0) {
        printf("Dancler CLI: An error occured during backend initialization.\nError code: %d\n", status);
        return status;
    }
    

    #ifndef NO_GUI_
    userInterface = gtk_application_new("com.github.heroes_of_balkan.dancler", G_APPLICATION_REPLACE);
    g_signal_connect(userInterface, "activate", G_CALLBACK(initialize_window_layout), NULL);
    status = g_application_run(G_APPLICATION(userInterface), argc, argv);
    g_object_unref(userInterface);
    #else
    userInterface = initialize_window_layout(NULL, &config);
    #endif

    unitialize_backend();
    
    return 0;
}