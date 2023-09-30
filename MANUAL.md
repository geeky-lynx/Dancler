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

> Note: There are no installation packages yet. Check how to build Dancler from scratch

## Building

Before building the project from scratch, make sure you have compiler for C installed (preferably `gcc`), PATH variables set up properly, GTK libraries installed and CMake installed.

For Linux, update your package repositories with your package managers.

For all Ubuntu flavors, Pop_OS, Linux Mint and other Ubuntu-based GNU/Linux systems/distributions: 
```sh
sudo apt update && sudo apt upgrade
sudo apt install build-essential cmake libgtk-4-1 libgtk-4-dev
```

For Debian, Zorin, VanillaOS and other Debian-based (excluding Ubuntu-based ones) systems:
```sh
sudo apt-get update && sudo apt-get upgrade
sudo apt install build-essential cmake libgtk-4-1 libgtk-4-dev
```

For Fedora, CentOS, Rocky, ALMA, Oracle Linux, Nobara and other Fedora or RHEL-based systems:
```sh
sudo dnf update
sudo dnf install gcc cmake gtk4 gtk4-devel
```

For openSUSE:
```sh
sudo zypper update
sudo zypper install gcc cmake gtk4
```

For Arch, Manjaro, EndeavourOS, ArcoLinux and other Arch-based systems:
```sh
sudo pacman -Syyu
sudo pacman -S base-devel gcc cmake gtk4
```

To build, go to `build` folder and run `cmake ..`, After it is done, run `cmake --build .`

Command looks like this:

```sh
# from the root of the repository
cd build
cmake ..
cmake --build .
```

Now, to run and execute, run `./dancler` or `.\dancler.exe` locating in current folder, depending on your operative system

```sh
# For Linux
./dancler
```
```powershell
# For Windows
.\dancler.exe
```