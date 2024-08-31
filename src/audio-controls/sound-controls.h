#include "../header.h"

#ifndef DANCLER_SOUND_CONTROLS_
#define DANCLER_SOUND_CONTROLS_ 1

/*
  int initialize_backend(): Initializes Miniaudio Engine for audio shit
  Parameters:
    - None
  Returns: (`int`) Error code from Miniaudio Engine initialization
    - `0`: Success / No error
    - Non `0`: "Houston, we have a problem"
*/
int initialize_backend(void);

/*
  int uninitialize_backend(): Destroys Miniaudio Engine from system stack; for quitting from program
  Parameters:
    - None
  Returns: (`int`) Error code from Miniaudio Engine uninitialization
    - `0`: Success / No error; Miniaudio Audio Engine is unitialized (destroyed)
    - Non `0`: "Houston, we have a problem"
*/
int unitialize_backend(void);

/*
  int set_volume_in_percents(const short volumePercentage): Change volume of program's playback audio
  Parameters:
    - `volumePercentage` (`const short`): Volume percentage to be set. Shall be in [0, 100] range
  Returns: None
*/
void set_volume_in_percents(short volumePercertange);

/*
  int load_audio_to_queue(const char *filename): Load audio file into Miniaudio Resource Manager from given filepath 
  Parameters:
    - `filename` (`const char*`): Unix-like filename path to look up for and load into Resource Manager
  Returns: (`int`) Error code from Miniaudio Engine initialization
    - `0`: Success / No error
    - Non `0`: "Cr*ap!"
*/
int load_audio_to_queue(const char filename[]);

/*
  int unload_audio_from_queue(): Removes audio data source from Miniaudio Resource Manager
  Parameters:
    - None
  Returns: (`int`) Error code from Miniaudio Engine initialization
    - `0`: Success / No error
    - Non `0`: "fricked up"
*/
int unload_audio_from_queue(void);

/*
  int toggle_playback(): Plays or stops playback of loaded audio from Miniaudio Resource Manager
  Parameters:
    - None
  Returns: (int) Previous playback state (negatives for errors)
    - `0`: Was stopped
    - `1`: Was playing
    - `-1`: Error: No loaded audio
*/
int toggle_playback(void);

/*
  void toggle_loop(): Enables or disabled playback loop
  Parameters:
    - None
  Returns: Nothing
*/
void toggle_loop(void);

/*
  void toggle_volume(): Mutes or unmutes program's playback; according to current volume percentage
  Parameters:
    - None
  Returns: Nothing
*/
void toggle_volume(void);

/*
  int is_audio_loaded(): Tells if audio file / data source is loaded into Miniaudio Project Manager
  Parameters:
    - None
  Returns: (int) State of Miniaudio Project Manager's data source / load
    - `0`: Audio file / Data source is NOT loaded
    - `1`: Loaded
*/
inline int is_audio_loaded(void);

#endif // DANCLER_SOUND_CONTROLS_
