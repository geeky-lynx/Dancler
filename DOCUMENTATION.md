> Note: Documentation is not complete.

# Table of Contents

1. Techstack, Philosophy & Vision
2. Structure
3. Functionality
4. Guidelines
5. API
6. Sources & Literature

> Note: This Table of Contents will be probably changed in the future. Also, since this is in beta, actual content may vary

# Techstack, Philosophy & Vision

This project uses C programming language as the main programming language. Reasons for that is minimalism, performance and lightweightness of the language. There is no need for something huge, like: Adobe Photoshop, Ableton Live, Youtube, etc.

Additionally, this project also uses GTK (GNOME ToolKit) for creating user interface, Miniaudio for sound playback, CMake to build on different platforms, and Git to manage versions.

GTK is GUI toolkit for creating desktop software. It is relatively easy to start and develop UI using pre-defined functions.

> Originally [Nuklear](https://immediate-mode-ui.github.io/Nuklear/doc/index.html) by Micha Mettke was supposed to be the chosen library for creating GUI elements. Problem with it was it does not have integrated display backends, meaning you either have to write your own display backend or use already existing backends like X, Wayland, OpenGL, Vulkan, Direct3D, etc. and then connect them together. Don't get me wrong! Nuklear is great, but I want this app to be simple to maintain.

Miniaudio is a single header file written in C by mackron. It is super easy to use and straight forward. It offers both high-level API and low-level API to common audio backends, supports Windows, Macintosh, Linux, BSD, Android, iOS and web/HTML.

CMake is a tool for building and creating cross-platform C/C++ software. This is great because you can have only one config file and build your project for GNU/Linux, BSD, Macintosh, Windows or other platforms.

Git is distributed version manager created by Linus Tolvards. It features easy version editing, collaboration and change tracker.

# Structure

#TODO

In this section will be explained folder structure, file structure, functions and et cetara.

## Architecture

#TODO

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

#TODO

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
void merge_mergesort(int array[], size_t left, size_t middle, size_t right) {
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

### Initial values at declaration is encouraged, except when you have lenghty functions or it's pointless to assume what value will it have

It's good idea to initialize its starting/default value before doing anything with it. This is especially true for pointers, since many dangerous problems are coming from badly handled pointers (e.g. dangling pointers, use-after-free, wild pointers,...), resulting in segmentation faults and race conditions, and even worse: undefined behaviours.

Having values initialized at start can help with readibility of code as well, reducing misunderstanding, vertical size and potential sneaky bugs.

Additionally, it is a practice to initialize variables to their default values/states when we are assuming or predicting an outcome, or just prepare it before we do something.

> I like the idea of RAII (Resource Acquisition In Initialization) from C++ and Rust, but it's impossible to impelemt RAII in C, so we will "immitate" it.

This "rule" can be broken if:
1. The line where initialization and declaration is too long, making it hard to contain whole line on screen's width. Instead, split declaration and initialization on two (or more) separate lines.
2. There is no point initializing its starting value when it is hard to assume and determine what is it going to be.

Example:
```c
// Compilant
enum ErrorCode error = NO_ERROR;
struct ImageFile *myImage = NULL;
long long unsigned int sumOfBeans = 0;
wchar_t *message = get_message_by(server);
pthread_t threadId; // no explicit need to set initial value because it's pointless

// Non-compilant
enum Result loadingResult = load_image_cover_from_audio_file("./songs/O-Zone - Dragonstea Din Tei (Official Music Video).mp3", 100, 100, NULL, 0); // bro i don't have a wide screen monitor
void *genericHandler; // Wild pointer! It's pointing to an unknown address; can lead to undefined behaviours!
```

## Naming conventions/schemas

When declaring new variables and constants, defining new functions, creating new structures, naming can be hard. Here are rules to help with that.

### If variables are not going to be changed/mutated, then they should be constants instead

It is hard to keep data's integrity to the fullest, especially in C. Bad use of pointers, accidental change, unexpected mutation, race condition, segmentation faults, undefined behaviours, etc.

This is simply here to tell if a variable is going to get changed somewhere later in the code is indeed a mutable variable, and a variable having its value unchanged during its scope it is in can be considered as a constant. If constant value is unchangeable, we won't accidentally reassign it (I bet we all have assigned to a variable instead of comparing if it is equal with something else as an condition in our `if` statements and spend hours depleting nerves over this silly mistake).

Function parameters, on the other hand, don't need to follow this rule, except if parameters in question are pointers to pieces of memory that don't change their content in function body. Declare those parameters as: `const T *pointerIdentifier` or `const T* pointerIdentifier` (both are the same).

The keyword `const` should be at the start of the variable declaration of scalar types, structures, unions, arrays, or enumerations (Example: `const unsigned id = 7`, `const long measurements[]` `const struct Display display = {/*whatever its fields are*/}`,...)

The keyword `const` depends where it should be put in pointer declarations, as they can mean different things (`T` is a type):

- Pointer to constant: `const T *identifier`
- Constant pointer to variable: `T* const identifier`
- Constant pointer to a constant: `const T* const identifier`
- Pointer to a constant pointer to a variable: `const T* const *identifier`
- ... and so on.

> I have took data immutability idea from functional languages like Elm, Haskell and Rust. Those languages enforce immutability, protecting data integrity and preventing from big set of bugs. It's pretty cool tho

Example:
```c
// Compilant
const time_t THAT_TIME_WE_KISSED = time(0); // This constant is expected to remain as such
long double GpsLocationLatitude = 69.420l; // This variable is expected to be mutated
// ...
GpsLocationLatitude = 44.2187l; // Variable is mutated
printf("Time: %f\n", THAT_TIME_WE_KISSED); // The value remains the same

// Non-compilant
long double MATH_PI = 3.141596l; // This constant is expected to be mutated???
time_t *pointerToTheMemories = &THAT_TIME_WE_KISSED; // Variable pointer is referenced to a constant
*pointerToTheMemories = NULL; // congrats! you now have JS const!!1
```

### Names/Identificators should describe its purpose (or "self-describing").

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
int ping(Connection x) {/* ... */}
```

### Identifier names should be named according to "what are they"

It is important to distinguish variables or constants from functions and structures. In that sense, the following table must be used:

| Identifiers             | Naming Style               |
| ----------------------- | -------------------------- |
| Variables               | camelCase                  |
| Objects                 | camelCase                  |
| Constants               | SCREAMING_SNAKE_CASE       |
| Functions               | snake_case                 |
| Structures              | PascalCase                 |
| Unions                  | PascalCase + "_"           |
| Enumerations            | PascalCase                 |
| Struct/Enum fields      | camelCase                  |
| Enum variants           | SCREAMING_SNAKE_CASE       |
| Preprocessor directives | SCREAMING_SNAKE_CASE + "_" |
| Source files            | kebab-case                 |

Examples:
```c
// Compilant
int measuredRoomTemperatureCelsius = 42;
static size_t soundsQueueCounter = queue_size(&soundQueue);
enum Week dayOfWeek = FRIDAY;
struct HumanEntity *humanEntity = malloc(48);
const double BANK_DEBT = -99.999'999; // Digit separator, available in C23 & C++14
union ColorRGBA_ color = { 0x9FA34077 };
FILE *userConfigFile = fopen("user-config.txt", "r");
STDIN_BUFFER_CLEAR_();
```

# API

#TODO

Here are located all functions, variables, constants and preprocessor directives, explaining what are they, what is their purpose and how to use.

# Sources & Literature

To get along with C, GTK, Miniaudio. CMake and Git, here are listed some useful hyperlinks.

## C programming language

Tutorials:
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
