#include "header.h"
// #define NO_GUI_

#ifndef NO_GUI_
#include "./gui/gui-main-window.c"
#else
#include "./gui/cli-main-window.c"
#endif


int main(int argc, char *argv[]) {
    int status = 0;
    ma_result result = MA_SUCCESS;
    ma_sound sound;
    ma_engine engine;
    ma_resource_manager resourceManager;
    ma_resource_manager_data_source dataSource;
    GtkApplication *userInterface;
    struct ProgramConfig config = { &sound, &engine, &resourceManager, &dataSource };

    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        perror("Failed to initialize audio engine.\n");
        return 2;
    }

    ma_resource_manager_config resourceManagerConfig = ma_resource_manager_config_init();
    result = ma_resource_manager_init(&resourceManagerConfig, &resourceManager);
    if (result != MA_SUCCESS) {
        perror("Failed to initialize resource manager.\n");
        return 3;
    }

    #ifndef NO_GUI_
    userInterface = gtk_application_new("com.github.heroes_of_balkan.dancler", G_APPLICATION_REPLACE);
    g_signal_connect(userInterface, "activate", G_CALLBACK(initialize_window_layout), (void*)&config);
    status = g_application_run(G_APPLICATION(userInterface), argc, argv);
    g_object_unref(userInterface);
    #else
    userInterface = initialize_window_layout(NULL, &config);
    #endif

    ma_engine_uninit(&engine);
    
    return 0;
}