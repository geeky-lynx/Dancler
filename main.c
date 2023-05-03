#include <stdio.h>
#include <errno.h>

#define MINIAUDIO_IMPLEMENTATION
#define MA_DEBUG_OUTPUT
#include "MiniAudio/miniaudio.h"

int main(int argc, char *argv[]) {

    ma_result result;
    ma_engine engine;
    if (argc < 2) {
        perror("too few arguments\n");
        return 1;
    }

    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        perror("Failed to initialize audio engin.\n");
        return 2;
    }

    ma_engine_play_sound(&engine, "FH.wav", NULL);

    printf("Press smth to quit lol.\n");
    getchar();
    
    ma_engine_uninit(&engine);
    
    return 0;
}