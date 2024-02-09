#include <stdio.h>
#include <errno.h>
#include <math.h>

#define MINIAUDIO_IMPLEMENTATION
#define MA_NO_NULL
#define MA_DEBUG_OUTPUT
#define MA_ENABLE_ONLY_SPECIFIC_BACKENDS
#ifdef _WIN32
    #define MA_ENABLE_WASAPI
#endif
#ifdef __linux__
    #define MA_ENABLE_PULSEAUDIO
#endif
#include "../libs/MiniAudio/miniaudio.h"

#define CLEAR_STDIN_BUFFER_() while ( (getchar()) != '\n' )

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
    _Bool isPlaying = 0;
    _Bool isLoaded = 0;
    

    while (isRunning) {
        printf("Enter command (enter \'h\' for help): \t");
        scanf("%c", &command);
        // while ((getchar()) != '\n'); // Buffer dumping
        // fflush(stdin);

        switch (command) {
            case 'q':
                printf("Stopping playback...\n");
                ma_sound_stop(&sound);
                if (isLoaded) {
                    printf("Unitializing playback...\n");
                    ma_sound_uninit(&sound);
                }
                printf("Unitializing the engine...\n");
                ma_engine_uninit(&engine);
                isPlaying = 0;
                isRunning = 0;
                isLoaded = 0;
                return 0; // Leave program
                break;
            case 'p':
                if (ma_sound_at_end(&sound)) {
                    printf("Old song reached the end. Enter a new song...\n");
                    ma_sound_stop(&sound);
                    ma_sound_uninit(&sound);
                    isRunning = 0;
                    isLoaded = 0;
                }
                if (isLoaded) {
                    printf("Song is already loaded.\nUnload first then try again.\n");
                    break;
                }
                printf("File location: ");
                scanf("%100s", parameter);
                result = ma_sound_init_from_file(&engine, parameter, 0, NULL, NULL, &sound);
                if (result != MA_SUCCESS) {
                    perror("Failed to read from file.");
                    printf("File: %s\n", parameter);
                    break;
                }
                ma_sound_start(&sound);
                isLoaded = 1;
                isPlaying = 1;
                break;
            case 's':
                ma_sound_stop(&sound);
                isPlaying = 0;
                break;
            case 'c':
                ma_sound_start(&sound);
                isPlaying = 1;
                break;
            case 'u':
                ma_sound_stop(&sound);
                ma_sound_uninit(&sound);
                isPlaying = 0;
                isLoaded = 0;
                break;
            case 'j':
                // TODO: set jump to seconds
                float second = 0;
                printf("Enter a position (in seconds): ");
                scanf("%f", &second);
                const unsigned long frameConstant =  2 * 48000;
                                    // Buffer * Channels * SampleRate * Seconds
                const unsigned long frame = frameConstant * second;
                printf("\tSecond: %f\n", second);
                printf("\tFrame Constant: %ld\n", frameConstant);
                printf("\tFrame: %ld\n", frame);
                printf("\tFrame: %ld\n", ma_engine_get_time_in_pcm_frames(&engine));
                // ma_sound_stop(&sound);
                ma_sound_seek_to_pcm_frame(&sound, frame);
                // ma_sound_start(&sound);
                break;
            case 'r':
                ma_sound_seek_to_pcm_frame(&sound, 0);
                ma_sound_start(&sound);
                isRunning = 1;
                isLoaded = 1;
                break;
            case 'v':
                printf("Volume (0 - 100): ");
                int volume = 50;
                scanf("%d", &volume);
                ma_sound_set_volume(&sound, volume / 100.0);
                break;
            case 'h':
                printf("\033[31m\'p\'\033[0m - Play & Load a song\n");
                printf("\033[31m\'s\'\033[0m - Stop current playing song\n");
                printf("\033[31m\'c\'\033[0m - Continue playback a song\n");
                printf("\033[31m\'v\'\033[0m - Change volume in %%-s\n");
                printf("\033[31m\'j\'\033[0m - Jump to a second\n");
                printf("\033[31m\'r\'\033[0m - Replay current song\n");
                printf("\033[31m\'u\'\033[0m - Unload current song\n");
                printf("\033[31m\'h\'\033[0m - Show commands\n");
                printf("\033[31m\'q\'\033[0m - Quit\n");
                break;
            default:
                printf("Invalid command!\n");
                break;
        }
        // while ((getchar()) != '\n'); // Buffer dumping
        CLEAR_STDIN_BUFFER_();
        // fflush(stdin);
    }
    return 0;
}