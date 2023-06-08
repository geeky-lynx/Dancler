#include "../../libs/MiniAudio/miniaudio.h"


void set_volume_controls_in_percents(ma_sound *audioSound, unsigned short volumePercertange) {
    ma_sound_set_volume(audioSound, volumePercertange / 100.0);
}