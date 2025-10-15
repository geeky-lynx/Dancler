#include "playlist.h"


static size_t playlistIndex = 0;
static size_t playlistSize = 3;

static Item playlist[3] = {
  1, "FH.mp3", "Fearless Hero",
  2, "ShesHomeless.mp3", "She\'s Homeless",
  3, "BG-HS.mp3", "Barbie Girl (Hardstyle)"
};

// this crap is temporary
Item get_item_at(size_t index) {
  return playlist[index];
}

int add_item(Item newItem) {
  return -1;
}

Item get_current_item() {
  return playlist[playlistIndex];
}

int playlist_go_previous() {
  playlistIndex = (playlistIndex - 1) % playlistSize;
  return 0;
}

int playlist_go_next() {
  playlistIndex = (playlistIndex + 1) % playlistSize;
  return 0;
}
