#ifndef DANCLER_GUI_CONTROLS_
#define DANCLER_GUI_CONTROLS_ 1

#include "../header.h"

/*
  void play_stop_current_audio(GtkWidget *titleLabel): Toggle audio playback through GUI
  Parameters:
    1. GtkWidget *titleLabel
        - GTK label to update to show current name of audio playback file
  Returns: Nothing
*/
void play_stop_current_audio(GtkWidget *titleLabel);

/*
  void start_previous_audio(GtkWidget *titleLabel): Start playing previous audio in playlist/queue
  Parameter:
    1. GtkWidget *titleLabel
        - GTK label to update to show previous name of audio playback file
  Returns: Nothing
*/
void start_previous_audio(GtkWidget *titleLabel);

/*
  void start_next_audio(GtkWidget *titleLabel): Start playing next audio in playlist/queue
  Parameter:
    1. GtkWidget *titleLabel
        - GTK label to update to show next name of audio playback file
  Returns: Nothing
*/
void start_next_audio(GtkWidget *titleLabel);

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
void change_volume(const GtkAdjustment *VOLUME_ADJUSTMENT_SRC);

#endif
