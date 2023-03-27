#include <stdio.h>
// #include "SDL/SDL2.h"

#define NK_IMPLEMENTATION
#include "NuklearUI/nuklear.h"

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio-master/miniaudio.h"

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

    // ma_device_start()
    ma_engine_play_sound(&engine, "FH.wav", NULL);

    printf("Press smth to quit lol.\n");
    getchar();
    
    ma_engine_uninit(&engine);
    
    return 0;


    // struct nk_context UIContext;
    // nk_init_default(&UIContext, &font);
    // nk_begin(&UIContext, "Show", );
}