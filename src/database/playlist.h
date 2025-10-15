#ifndef DANCLER_PLAYLIST_
#define DANCLER_PLAYLIST_ 1

#include "../common/song-info.h"

typedef struct _Item {
    int num;
    char *filepath;
    char *title;
} Item;

enum {
    COLUMN_ITEM_NUM,
    COLUMN_ITEM_FILEPATH,
    COLUMN_ITEM_TITLE,

    NUM_ITEM_COLUMNS
};

enum {
    COLUMN_NUMBER_TEXT,
    NUM_NUMBER_COLUMNS
};


// Temporary
Item get_item_at(size_t index);
int add_item(Item newItem);
Item get_current_item();

int playlist_initialize_empty();

int playlist_initialize_from_file(FILE* filepath);

size_t playlist_get_size();

size_t playlist_get_index();

int playlist_set_index(size_t newIndex);

int playlist_go_next();

int playlist_go_previous();

SongInfo playlist_get_song_info(size_t index);

const char* playlist_get_song_filepath(size_t index);

int playlist_insert_into(size_t indexAfter, SongInfo newEntry);

int playlist_remove_at(size_t index);

int playlist_find(const char *search);

int playlist_destroy();

#endif /* DANCLER_PLAYLIST_ */
