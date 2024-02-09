# Update no. 1.0.0.4-3

## Commit "Experimentation"

I had a little problem around music "queues"

## Commit "Set debug flags for CMake by default"

This change is going to be applicable during alpha and early beta stages of development.

## Commit "Clearing, defining, refactoring, working on normal API"

You've probably seen `#include "source-file.c"`... Also, backend data is moved to another file from `src/main.c`.

## Commit "Cleanings and minor fixes in documentation"

There were some misspells of words and wacky sentences in documentation. There are also some `#TODO` notices where changes are needed.

Oh, naming conventions are better visually concluded now.

# Update no. 1.0.0.4-2

## Commit "Im lost"

This commit includes multiple changes I can't explain well (i know I am breaking the documentation):

- Moved placeholder `.png` icons from `/src/assets/` to `/build/assets/`
- Added new songs in `/experiments` called "Barbie Girl (Hardstyle version)" and "She's Homeless x Spider-Man India",  files: `BG-HS.mp3` & `ShesHomeless.mp3`, respectively
- Shameful attempt to add unit testing
- Removed CLI "logging" in backend functions in file `/src/audio-controls/sound-control.c`
- Added button events in GUI
- New "functions"
- A bit more experimenting
- Added frontend-backend link (if that is called a "link")

# Update no. 1.0.0.4-1

## Commit "Implement header.h in project"

Creating a `header.h` file and doing all preprocessing requirements makes centralized place to do all of that. Plus, there will be no `#include` clashes.

Also, app startup execution is faster because of `MA_ENABLE_ONLY_SPECIFIC_BACKENDS` and enabling backends for each platform they support.

## Commit "Update .gitignore and build settings"

`/src/assets` folder is copied to `/build/assets` for Dancler to use custom icons (which will be implemented eventually).

asdf

# Update no. 1.0.0.4

## Commit "CMakeLists.txt GTK inclusion fix"

Before building app with `cmake ..` and `cmake --build .` didn't work because of improper `include_*()` commands. Now, those are fixed and you can freely build with CMake again!

## Commit "experimentation with callbacks"

Me experimenting with GTK callbacks. Planned to be implemented into the Dancler.

## Commit "Improve audio control functions"

There were some compiler bugs in some functions. More improvement on the way.

## Commit "Improve documentation & manual"

In manual, step-by-step build process is now available on major GNU/Linux distributions. It includes how to build Dancler with CMake.

In documentation, software architecture is better defined.

# Update no. 1.0.0.3

## Commit "New Playback functions created"

New functions are created:
- `set_volume_controls_in_percents()` - Change playback volume
- `load_audio_to_queue()` - Push a new audio into playback queue
- `unload_audio_from_queue()` - Pop an already existing audio from playback queue
- `toggle_playback()` - Play or pause current playback
- `toggle_loop()` - Enable or disable playback loop

## Commit "super small microscopic update of gui callbacks"

There are no changes that affect the product. It is about to be in development after completing audio playback controls.

# Update no. 1.0.0.2

## Commit "Fix signatures in CMake"

There were errors about GTK linking, missing required signatures in functions `target_link_libraries`, `target_include_directories` and `target_link_directories`. The signature `PRIVATE` has been set to all of those functions.

## Commit "Updated main window layout"

More GUI elements have been added and old ones have been rearranged. Also, new window layout mockup has been changed. It will be revealed in next update.

## Commit "New icons/images for navigation"

New temporary `.png` images are created in `/src/assets` folder:
- `no-cover.png` - Album cover placeholder, if there is no cover
- `play.png` - Play button
- `prev.png` - Previous song button
- `next.png` - Next song button
- `mute.png` - Mute audio button

# Update no. 1.0.0.1

## Commit "Fulfilling the documentation"

There are new guidelines for defining functions, like: "If variables have same data type, write them in the 'compact way', with same or similar level of indentation" and "Initial values should be set at start, except by lenghty functions"

## Commit "New experiments"

Those files don't affect the project in any way. They are used for learning purposes only.

## Commit "README.md checkboxes fix"

Checkboxes were not rendered properly. By adding space in each "box" should let Github properly render them.

## Commit "Cleaning main.c"

The `main.c` file contained program load a sound into memory and play it. This is removed since this is not the place to handle these stuffs. Instead, `main.c` will initialize everything needed for the MP3 player.

## Commit "Create new files for GUI and audio controls"

New files were created:
- `sound-control.c` - Audio controlling system (Not sure; may be changed in the future)
- `gui-main-window.c` - Create the user interface and window
- `gui-playback-controls.c` - Playback control functionalities, like play, stop, volume, next,... (Not sure)
- `gui-playback-information.c` - Playback information, like timing, sound title, authors,... (Not sure)

## Commit "Update CMakeList.txt"

New lines have been added to include GTK library and its compilation flags. It's still not complete, but it will be acting as a base.

# Update no. 1

Start