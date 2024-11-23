#include "header.h"
#include "./audio-controls/sound-controls.h"
#include "./gui/interface-api.h"

static const char APPLICATION_NAME[] = "com.github.heroes_of_balkan.dancler";

int main(int argc, char *argv[]) {
    int status;
    GtkApplication *userInterface;
    
    status = initialize_backend();
    if (status != 0) {
        printf("Dancler CLI: An error occured during backend initialization.\nError code: %d\n", status);
        return status;
    }

    userInterface = gtk_application_new(APPLICATION_NAME, G_APPLICATION_REPLACE);
    g_signal_connect(userInterface, "activate", G_CALLBACK(initialize_window_layout), NULL);
    status = g_application_run(G_APPLICATION(userInterface), argc, argv);
    g_object_unref(userInterface);

    unitialize_backend();
    
    return status;
}
