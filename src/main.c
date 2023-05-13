#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#define MINIAUDIO_IMPLEMENTATION
#define MA_NO_NULL
#define MA_DEBUG_OUTPUT
#include "../libs/MiniAudio/miniaudio.h"

int main(int argc, char *argv[]) {

    ma_result result;
    ma_engine engine;
    ma_sound sound;
    if (argc < 2) {
        perror("too few arguments\n");
        return 1;
    }

    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        perror("Failed to initialize audio engine.\n");
        return 2;
    }

    // ma_engine_play_sound(&engine, argv[1], NULL);
    result = ma_sound_init_from_file(&engine, argv[1], 0, NULL, NULL, &sound);
    if (result != MA_SUCCESS) {
        perror("Failed to read from file.");
        printf("File: %s\n", argv[1]);
        return result;
    }
    ma_sound_start(&sound);

    sleep(2);
    ma_sound_stop(&sound);
    printf("Press enter to continue.\n");
    getchar();
    
    ma_sound_set_volume(&sound, 0.05);
    ma_sound_seek_to_pcm_frame(&sound, 100000);
    ma_sound_start(&sound);

    printf("Press smth to quit lol.\n");
    getchar();

    ma_sound_stop(&sound);
    ma_sound_uninit(&sound);
    ma_engine_uninit(&engine);
    
    return 0;
}