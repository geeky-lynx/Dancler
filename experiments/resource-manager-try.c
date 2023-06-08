#include <stdio.h>
#include <windows.h>


#define MINIAUDIO_IMPLEMENTATION
#define MA_NO_NULL
#define MA_DEBUG_OUTPUT
#include "../libs/MiniAudio/miniaudio.h"

int main() {
    ma_resource_manager_config resourceManagerConfig;
    ma_resource_manager resourceManager;
    ma_result result;
    ma_device device;
    ma_sound sound;
    ma_engine engine;
    ma_resource_manager_data_source dataSource;

    resourceManagerConfig = ma_resource_manager_config_init();
    result = ma_resource_manager_init(&resourceManagerConfig, &resourceManager);

    if (result != MA_SUCCESS) {
        printf("Error occured while initializing resource manager.\n");
        return -1;
    }

    result = ma_resource_manager_data_source_init(&resourceManager, "FH.mp3", 0, NULL, &dataSource);
    if (result != MA_SUCCESS) {
        // ma_resource_manager_destroy(&resourceManager);
        printf("Error occured while reading from file.\n");
        return -1;
    }
    result = ma_engine_init(NULL, &engine);
    result = ma_sound_init_from_data_source(&engine, &dataSource, 0, NULL, &sound);
    Sleep(5000);
    ma_sound_start(&sound);
    getchar();
    ma_sound_stop(&sound);
    ma_sound_uninit(&sound);

    ma_resource_manager_data_source_uninit(&dataSource);

    printf("Successfully initialized!\n");
    return 0;
}