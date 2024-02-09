#include <stdio.h>


#define MINIAUDIO_IMPLEMENTATION
#define MA_NO_NULL
#define MA_ENABLE_ONLY_SPECIFIC_BACKENDS
#ifdef _WIN32
    #define MA_ENABLE_WASAPI
    #include <windows.h>
    #define SLEEP(x) Sleep(x)
#endif
#ifdef __linux__
    #define MA_ENABLE_PULSEAUDIO
    #include <unistd.h>
    #define SLEEP(x) sleep(x / 1000)
#endif
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
    const char *queue[3] = {"FH.mp3", "ShesHomeless.mp3", "BG-HS.mp3"};

    resourceManagerConfig = ma_resource_manager_config_init();
    result = ma_resource_manager_init(&resourceManagerConfig, &resourceManager);

    if (result != MA_SUCCESS) {
        printf("Error occured while initializing resource manager.\n");
        return -1;
    }

    result = ma_resource_manager_data_source_init(&resourceManager, queue[0], 0, NULL, &dataSource);
    if (result != MA_SUCCESS) {
        // ma_resource_manager_destroy(&resourceManager);
        printf("Error occured while reading from file.\n");
        return -1;
    }

    result = ma_engine_init(NULL, &engine);
    result = ma_sound_init_from_data_source(&engine, &dataSource, 0, NULL, &sound);
    


    // Sleep(5000);
    ma_sound_start(&sound);
    getchar();
    SLEEP(2000);
    ma_sound_stop(&sound);
    printf("%p\n", sound.pDataSource);
    printf("%p\n", sound.pResourceManagerDataSource);
    printf("%d!\n", sound.ownsDataSource);
    ma_sound_uninit(&sound);
    printf("%p\n", sound.pDataSource);
    printf("%p\n", sound.pResourceManagerDataSource);
    printf("%d!\n", sound.ownsDataSource);
    result = ma_resource_manager_data_source_init(&resourceManager, queue[1], 0, NULL, &dataSource);
    result = ma_sound_init_from_data_source(&engine, &dataSource, 0, NULL, &sound);
    if (result != MA_SUCCESS) {
        printf("couldnt resource man ds init\n");
        return -123;
    }
    // result = ma_sound_init_from_data_source(&engine, &dataSource, 0, NULL, &sound);
    if (result != MA_SUCCESS) {
        printf("couldn't load a sound bro\n");
        return 1;
    }
    ma_sound_start(&sound);
    SLEEP(5000);
    ma_sound_stop(&sound);
    ma_sound_uninit(&sound);

    ma_resource_manager_data_source_uninit(&dataSource);

    printf("Successfully initialized!\n");
    return 0;
}