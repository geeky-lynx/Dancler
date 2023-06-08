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