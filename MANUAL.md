> Note: Manual is not complete. Some key sections will be missing.

# Table of Contents

1. Introduction
2. Getting Started
3. Installation & Building
    3.1. Installation
    3.2. Building
4. User Interface
5. Setting up
6. Configuration & Themeing

# Installation & Building

## Installation

## Building

Before building the project from scratch, make sure you have compiler for C installed (preferably `gcc`), PATH variables set up properly, GTK libraries installed and CMake installed.

To build, go to `build` folder and run `cmake ..`, After it is done, run `cmake build`

Command looks like this:

```sh
# from the root of the repository
cd build
cmake ..
cmake build
```

Now, to run and execute, run `./dancler` or `.\dancler.exe` locating in current folder, depending on your operative system

```sh
# For Linux
./dancler

# For Windows
.\dancler.exe
```