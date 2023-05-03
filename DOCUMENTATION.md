> Note: Documentation is not complete.

# Table of Contents

1. Techstack, Philosophy & Vision
2. Structure
3. Functionality
4. Rules
5. API
6. Sources & Literature

# Techstack, Philosophy & Vision

This project uses C programming language as the main programming language. Reasons for that is minimalism, performance and lightweightness of the language. There is no need for something huge, like: Adobe Photoshop, Ableton Live, Youtube, etc.

Additionally, this project also uses GTK (GNOME ToolKit) for creating user interface, Miniaudio for sound playback, CMake to build on different platforms, and Git to manage versions.

GTK is GUI toolkit for creating desktop software. It is relatively easy to start and develop UI using pre-defined functions.

> Originally [Nuklear](https://immediate-mode-ui.github.io/Nuklear/doc/index.html) by Micha Mettke was supposed to be the chosen library for creating GUI elements. Problem with it was it does not have integrated display backends, meaning you either have to write your own display backend or use already existing backends like X, Wayland, OpenGL, Vulkan, Direct3D, etc. and then connect them together.

Miniaudio is a single header file written in C by mackron. It is super easy to use and straight forward. It offers both high-level API and low-level API to common audio backends, supports Windows, Macintosh, Linux, BSD, Android, iOS and web/HTML.

CMake is a tool for building and creating cross-platform C/C++ software.

Git is distributed version manager created by Linus Tolvards.

# Structure

# Rules

Rules are here to 

## Naming conventions

### Variables and objects should be named in snake_case

### Constants should be named in SCREAMING_SNAKE_CASE

### Functions should be named in camelCase

### Structures should be named in UpperCamelCase

### Preprocessor directives should be named in SCREAMING_SNAKE_CASE, with '_' at the end

### Files should be named in kebab-case

### Names should be descriptive, giving meaning to it

# API

Here are located all functions, variables, constants and preprocessor directives, explaining what are they, what is their purpose and how to use.

# Sources & Literature

To get along with C, GTK, Miniaudio and CMake, here are listed some useful hyperlinks.

## C programming language

- [Javapoint](https://www.javatpoint.com/c-programming-language-tutorial)
- [Geeks For Geeks](https://www.geeksforgeeks.org/c-language-introduction/)
- [W3School](https://www.w3schools.com/c/c_intro.php)
- [Programiz](https://www.programiz.com/c-programming)

## GTK (GNOME ToolKit)

- [GTK Docs](https://docs.gtk.org/gtk4/index.html)

## Miniaudio

- [Miniaudio programming manual](https://miniaud.io/docs/manual/index.html)

## CMake

- [CMake online documentation](https://cmake.org/documentation/)

## Git

- [Git documentation](https://git-scm.com/doc)