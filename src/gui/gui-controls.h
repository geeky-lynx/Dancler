#include "../header.h"

#ifndef DANCLER_GUI_CONTROLS_
#define DANCLER_GUI_CONTROLS_ 1

/*
  void play_stop_current_audio(): Toggle audio playback through GUI
  Parameters:
    - None
  Returns: Nothing
  
*/
void play_stop_current_audio();

/*
  void start_previous_audio(): Start playing previous audio in playlist/queue
  Parameter:
    - None
  Returns: Nothing
*/
void start_previous_audio(void);

/*
  void start_next_audio(): Start playing next audio in playlist/queue
  Parameter:
    - None
  Returns: Nothing
*/
void start_next_audio(void);

/*
  void mute_audio(): Toggle volume on/off of the software
  Parameter:
    - None
  Returns: Nothing
*/
void mute_audio(void);

#endif
