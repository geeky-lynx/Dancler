#ifndef DANCLER_GUI_CONTROLS_
#define DANCLER_GUI_CONTROLS_ 1

#include "../header.h"

#include <gtk/gtk.h>

/*
  void play_stop_current_audio(): Toggle audio playback through GUI
  Parameters: None
  Returns: Nothing
*/
void play_stop_current_audio();

/*
  void start_previous_audio(): Start playing previous audio in playlist/queue
  Parameter: None
  Returns: Nothing
*/
void start_previous_audio();

/*
  void start_next_audio(): Start playing next audio in playlist/queue
  Parameter: None
  Returns: Nothing
*/
void start_next_audio();

/*
  void mute_audio(): Toggle volume on/off of the software
  Parameter:
    - None
  Returns: Nothing
*/
extern inline void mute_audio(void);



/*
    void change_volume(const GtkAdjustment *VOLUME_ADJUSTMENT_SRC): Change playback volume as GUI volume slider is changed
    Parameter:
        1. const GtkAdjustment *VOLUME_ADJUSTMENT_SRC
            - Source of GTK Adjustment which value has been changed
    Returns: Nothing
*/
void change_volume(GtkAdjustment *volumeAdjustment, void *data);

#endif
