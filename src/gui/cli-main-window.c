#include "../header.h"

int initialize_window_layout(void *application, void *data) {
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
                ma_sound_stop(data->sound);
                if (isLoaded) {
                    printf("Unitializing playback...\n");
                    ma_sound_uninit(data->sound);
                }
                printf("Unitializing the engine...\n");
                ma_engine_uninit(data->engine);
                isPlaying = 0;
                isRunning = 0;
                isLoaded = 0;
                return 0; // Leave program
                break;
            case 'p':
                if (ma_sound_at_end(data->sound)) {
                    printf("Old song reached the end. Enter a new song...\n");
                    ma_sound_uninit(data->sound);
                    isRunning = 0;
                    isLoaded = 0;
                }
                if (isLoaded) {
                    printf("Song is already loaded.\nUnload first then try again.\n");
                    break;
                }
                printf("File location: ");
                scanf("%100s", parameter);
                result = ma_sound_init_from_file(&engine, parameter, 0, NULL, NULL, data->sound);
                if (result != MA_SUCCESS) {
                    perror("Failed to read from file.");
                    printf("File: %s\n", parameter);
                    break;
                }
                ma_sound_start(data->sound);
                isLoaded = 1;
                isPlaying = 1;
                break;
            case 's':
                ma_sound_stop(data->sound);
                isPlaying = 0;
                break;
            case 'c':
                ma_sound_start(data->sound);
                isPlaying = 1;
                break;
            case 'u':
                ma_sound_stop(data->sound);
                ma_sound_uninit(data->sound);
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
                printf("\tFrame: %ld\n", ma_engine_get_time_in_pcm_frames(data->engine));
                // ma_sound_stop(&sound);
                ma_sound_seek_to_pcm_frame(&sound, frame);
                // ma_sound_start(&sound);
                break;
            case 'r':
                ma_sound_seek_to_pcm_frame(data->sound, 0);
                ma_sound_start(data->sound);
                isRunning = 1;
                isLoaded = 1;
                break;
            case 'v':
                printf("Volume (0 - 100): ");
                int volume = 50;
                scanf("%d", &volume);
                ma_sound_set_volume(data->sound, volume / 100.0);
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
    }
}