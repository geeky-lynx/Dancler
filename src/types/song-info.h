#ifndef DANCLER_SONG_INFO_
#define DANCLER_SONG_INFO_ 1

#include "../header.h"
#include "./german-string.h"

struct SongInfo {
    uint32_t trackNumber; // barely anyone will have over 4B tracks
    GermanString title;
    GermanString author;
    GermanString album;
    GermanString genre;
    uint16_t year;
    uint8_t rating;
    uint8_t bitrate;
    uint64_t durationInSeconds;
    struct hidden { // Struct named as a "field"
        unsigned char *directory;
        unsigned char *filename;
    };
};

#endif /* DANCLER_SONG_INFORMATION_ */
