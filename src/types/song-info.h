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

enum SongInfoColumn {
    COLUMN_TRACK_NUMBER,
    COLUMN_TITLE,
    COLUMN_AUTHOR,
    COLUMN_ALBUM,
    COLUMN_GENRE,
    COLUMN_YEAR,
    COLUMN_RATING,
    COLUMN_BITRATE,
    COLUMN_DURATIONS_SECONDS,

    NUMBER_OF_COLUMNS /* Number of "visible" fields for playlist  */
}

#endif /* DANCLER_SONG_INFORMATION_ */
