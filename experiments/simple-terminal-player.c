#include <stdio.h>
#include <errno.h>

#define MINIAUDIO_IMPLEMENTATION
#define MA_NO_NULL
#define MA_DEBUG_OUTPUT
#include "../libs/MiniAudio/miniaudio.h"

#define CLEAR_STDIN_BUFFER_() while ( (getchar()) != '\n' );

int main(int argc, char *argv[]) {

    ma_result result;
    ma_engine engine;
    ma_sound sound;

    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        perror("Failed to initialize audio engine.\n");
        return 2;
    }
    
    char command;
    char parameter[100];
    _Bool isRunning = 1;

    while (isRunning) {
        printf("Enter command:\t");
        scanf("%c", &command);
        // while ((getchar()) != '\n'); // Buffer dumping
        // fflush(stdin);

        switch (command) {
            case 'q':
                ma_sound_stop(&sound);
                ma_sound_uninit(&sound);
                ma_engine_uninit(&engine);
                isRunning = 0;
                return 0; // Leave program
                break;
            case 'p':
                printf("File location: ");
                scanf("%s", parameter);
                result = ma_sound_init_from_file(&engine, parameter, 0, NULL, NULL, &sound);
                if (result != MA_SUCCESS) {
                    perror("Failed to read from file.");
                    printf("File: %s\n", parameter);
                    continue;
                }
                ma_sound_start(&sound);
                break;
            case 's':
                ma_sound_stop(&sound);
                break;
            case 'c':
                ma_sound_start(&sound);
                break;
            case 'j':
                // TODO: set jump to seconds
                break;
            case 'v':
                printf("Volume (0 - 100): ");
                int volume = 50;
                scanf("%d", &volume);
                ma_sound_set_volume(&sound, volume / 100.0);
                break;
            default:
                printf("Invalid command.\nEnter \'h\' for help.\n");
                break;
        }
        while ((getchar()) != '\n'); // Buffer dumping
        fflush(stdin);
    }
    return 0;
}