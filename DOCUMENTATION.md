> Note: Documentation is not complete.

# Table of Contents

1. Techstack, Philosophy & Vision
2. Structure
3. Functionality
4. Guidelines
5. API
6. Sources & Literature

# Techstack, Philosophy & Vision

This project uses C programming language as the main programming language. Reasons for that is minimalism, performance and lightweightness of the language. There is no need for something huge, like: Adobe Photoshop, Ableton Live, Youtube, etc.

Additionally, this project also uses GTK (GNOME ToolKit) for creating user interface, Miniaudio for sound playback, CMake to build on different platforms, and Git to manage versions.

GTK is GUI toolkit for creating desktop software. It is relatively easy to start and develop UI using pre-defined functions.

> Originally [Nuklear](https://immediate-mode-ui.github.io/Nuklear/doc/index.html) by Micha Mettke was supposed to be the chosen library for creating GUI elements. Problem with it was it does not have integrated display backends, meaning you either have to write your own display backend or use already existing backends like X, Wayland, OpenGL, Vulkan, Direct3D, etc. and then connect them together. Don't get me wrong! Nuklear is great, but I want this app to be simple to maintain.

Miniaudio is a single header file written in C by mackron. It is super easy to use and straight forward. It offers both high-level API and low-level API to common audio backends, supports Windows, Macintosh, Linux, BSD, Android, iOS and web/HTML.

CMake is a tool for building and creating cross-platform C/C++ software.

Git is distributed version manager created by Linus Tolvards.

# Structure

In this section will be explained folder structure, file structure, functions and et cetara.

## Arhcitecture

Folder architecture of the repo looks like this:

```
./(root)
    /build
    /docs-assets
    /experiments
    /libs
        /MiniAudio
    /src
        /assets
        /audio-controls
        /gui
```

`/build` folder is location where building with CMake should be done.

In `/docs-assets` folder are assets used in [DOCUMENTATION.md](./DOCUMENTATION.md), [MANUAL.md](./MANUAL.md), [CONTRIBUTION.md](./CONTRIBUTION.md), and other Markdown files.

`/experiments` don't affect anything in this repository. It's here just for some experiments to test some library's feature, prototyping, innovate,...

`/libs` contain libraries required for program to work, like Miniaudio. 

`/src` is where all the source code is available. All code that is written has to be located here.

`/src/audio-controls` folder contains functions controlling audio playback through Miniaudio.

`/src/gui` folder contains functions and instructions for providing Graphical User Interface (GUI) and graphical event handling through function callbacks.

# Guidelines

Guidelines are here to guide developers, contributors and maintainers creating Dancler. They will be divided by categories with rules. Each rule is explained (what, why, how, where, when,...), with some examples to better understand the rule.

## Defining functions

(theoretically) Functions are everything in C. Well-written functions can do very complex tasks.

Since there is no inheritance, polymorphism, or lambda/anomyous functions, we need to be smart. Here are "small" rules for defining functions.

### Declare variables and constants at start of definition

There should be special section in the function block dedicated to variable declarations. In one place developer should know which variables are used. Also, we want to avoid declarations spread out of the function block.

This rule does not need to be applied for temporary variables in function.

Example:
```c
// Compilant
void merge_mergesort(int arr[], size_t left, size_t middle, size_t right) {
    size_t  leftIndex = 0,
            rightIndex = 0,
            leftHalfSize = middle - left + 1,
            rightHalfSize = right - middle;

    int arrayLeftHalf[leftHalfSize],
        arrayRightHalf[rightHalfSize];
    // ... 
}

// Non-compilant
size_t convert_int_to_string(int number, char newString[]) {
    size_t length = 0;
    while (number) {
        short int firstDigit = number % 10;
        number /= 10;
        length++;
        static size_t index = 0;
        newString[index] = firstDigit + 48; // 48 = '0', so 0 + '0' = '0'
    }

    size_t left = 0;
    size_t right = length;

    // Reverse string
    while (left < right) 
        newString[left] = newString[right];

    return length;
}
```

### If variables have same data type, write them in the "compact way", with same or similar level of indentation

This is somewhat to explain

Example:
```c
// Compilant
long double coordinateX,
            coordinateY,
            coordinateZ;
float       rotation,
            scaleX,
            scaleY;

// Non-compilant
vector_t vectorA;
vector_t vectorB;
vector_t vectorC; // too much typing though
```

### Initial values at declaration is encouraged, except when you have lenghty functions

Having values initialized at start can help with readibility of code, reducing complexity or other, so it is recommended to initialize starting value if we are assuming/predicting a result (for an example).

Only exception is when you use functions with long names. Because of length of function names and its parameters, value initialization can't fit in one single line of a display, breaking it in more lines or hiding rest of it, and then you need to use a horizontal scroll.

Example:
```c
// Compilant
enum ErrorCode error = NO_ERROR;
struct ImageFile *myImage = NULL;
wchar_t message[MAX_MSG_LENGTH] = get_message_by(server);
pthread_t threadId; // no explicit need to set initial value

// Non-compilant
enum Result loadingResult = load_image_cover_from_audio_file("./songs/O-Zone - Dragonstea Din Tei (Official Music Video).mp3", 100, 100, NULL); // bro i don't have a wide screen monitor
```

## Naming conventions/schemas

When declaring new variables and constants, defining new functions, creating new structures, naming can be hard. Here are rules to help with that.

### Names/Identificators should be descriptive to its purpose.

Names are used to identificate variables, functions, properties, constants,... and names tell us what they are supposed to do or contain. For variables, what value are they storing and of what type (let's say `temperature` has 60.9f as value, but 60.9f degrees of what? Celsius? Kelvin? Fahrenheit?); for functions, what is it doing (function `play()` can do variety of jobs: play video, audio, game, slideshow, presentation, sex tape, etc.); and so on.

Temporary variables don't need to follow this rule, but they still can't be named however somebody wants. Just naming `tmp` or `temporary` is enough, but not `x`, `t`, `abcdef`,...

Examples:
```c
// Compilant
double temperatureInCelsius = 47.8; // Temperature in Greece & Turkey during summer
uintmax_t playbackErrorCode = 2;
int16_t audioSample16Bit = read_sample_16bit_from_audio_file_at_pcm_frame(FILE *audioSourceFile, ssize_t frameInPCM);

// Non-compilant
_Complex z;
double temp = 80.21;
char pass[9] = "password";
int ping(Connection x);
```

### Variables and objects should be named in camelCase

To differentiate variables from functions (which are mostly written in snake_case), variables will be written in camelCase.

Examples:
```c
// Compilant (Good)
int myLocalVariable;
Week dayOfWeek = Friday;
static soundsQueueCounter;

// Non-compilant
date_t Year;
ssize_t INDEX = -1;
bool is_showering = false;
```

### Constants should be named in SCREAMING_SNAKE_CASE

Most common way to write constants in any language is right in SCREAMING_SNAKE_CASE, like Python, JavaScript, Java (I think), C, and others.

Examples:
```c
// Compilant
const double NUMBER_PI = 3.14259;
const long double NATURAL_NUMBER_E = 2.17281828;
const char8_t FINAL_GRADE = u'A';
const int const *PERMANENT_POINTER_TO_AUDIO_ENGINE = &audioEngine;

// Non-compilant
const char leave = 'c';
const time_t one_time_when_bad_happened_for_humankind = nuke(cities, 2); // discovery of hentai
const void *somethingOnHeap = (void *) malloc(12);
const _Bool HasLovePartner = 0;
```

### Functions should be named in snake_case

Most function names written in GTK and Miniaudio are in snake_case. To make new functions familiar with each other, function names will be in snake_case.

Examples:
```c
// Compilant
int convert_from_string_to_int(const restrict char string[], size_t length);
wchar_t* get_string_from_clock_now();
void clear_playlist();

// Non-compilant
float64_t Rickroll(char *message);
time_t readTime(restrict float *unixTime);
_Bool IS_CRYING(struct Person person);
```

### Structures and enumerations should be named in UpperCamelCase

In other languages like Java, JavaScript, and even Python, usually have class names in UpperCamelCase. To keep this "trend", structs and enums will be named in UpperCamelCase. Also, we want to differentiate from variables, constants, functions,...

Properties of structures should be named in lowerCamelCase, while enumeration values should be named in SCREAMING_SNAKE_CASE.

Also, properties don't need to be very descriptive.

Examples:
```c
// Compilant
struct WorkingPerson {
    wchar_t firstName[15];
    wchar_t lastName[15];
    unsigned short int age;
    float revenue;
};
enum DaysInWeek {MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY};

// Non-compilant
struct my_bro {/* ... */};
struct shoppingCart {/* ... */};
enum FEELINGS {/* ... */};
enum schooldegrees {/* ... */};
```

### Unions should be named in UpperCamelCase, with `_` at the end

Since unions and structs are very similar, adding `_` as suffix to its type name will put a period that the object is not a struct object.

Properties should be named in lowerCamelCase.

Examples:
```c
// Compilant
union WhatIsOnMind_ {
    struct Food apples;
    unsigned char crush[11];
    short int sheepsCount;
};

// Non-compilant
union WorkingOn {
    struct Job JOB;
    struct Hobby hobby_at_home;
    void Nothing;
}
```

### Preprocessor definitions should be named in SCREAMING_SNAKE_CASE, with `_` at the end

Since constants are already named in SCREAMING_SNAKE_CASE, underscore (`_`) will be added as suffix to it to make differences between normal constants and preprocessor definitions.

Examples:
```c
// Compilant
#define MAX_STRING_LENGTH_ 1001
#define SECRET_CODE_ 12345678
#define SLEEP_(ms) sleep(ms / 1000)

// Non-compilant
#define postal_code 555
#define ipAddress "21.266.69.420" // this IP doesn't exist
#define PainfulTrueFalse rand() % 2 ? true : false
```

### Files should be named in kebab-case

To make it easier to go through files via terminal (by using CTRL + arrows for an example) and to not use double quotes when writing commands in Bash, Powershell, Zsh,... use kebab-case for files in this repository. This rule is applied to source code, assets (images, videos, audio), Markdown files,...

Files required to have different naming conventions by other programs are excluded from this rule. Some of those files are `CMakeList.txt` and `.gitignore`.

Examples:
```sh
# Compilant
mkdir my-new-directory
vim gui-buttons.c
ls # icon-play.svg  icon-stop.svg   icon-pause.svg  svg-to-png.c ...

# Non-compilant
gcc my first program.c
gcc "my first program.c"
clang hello_world.cpp
```

# API

Here are located all functions, variables, constants and preprocessor directives, explaining what are they, what is their purpose and how to use.

# Sources & Literature

To get along with C, GTK, Miniaudio. CMake and Git, here are listed some useful hyperlinks.

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