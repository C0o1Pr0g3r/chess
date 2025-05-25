# Chess

## Table of contents

- [Introduction](#introduction)
- [About](#about)
- [Technologies used](#technologies-used)
- [Downloading](#downloading)
- [Building](#building)
  - [Build for Linux](#build-for-linux)
  - [Build for the Web](#build-for-the-web)
    - [Emscripten](#emscripten)
      - [Note on Emscripten programs](#note-on-emscripten-programs)
    - [SFML library compiled for the Web](#sfml-library-compiled-for-the-web)
- [Launch of the project](#launch-of-the-project)
  - [On Linux](#on-linux)
  - [In the browser](#in-the-browser)

## Introduction

You can try playing by following the [link](https://c0o1pr0g3r.itch.io/chess).

To change the chess API provider, press the middle mouse button, no matter what part of the application you are in (main menu, game settings, the game itself).

## About

Chess is a project that implements a well-known strategy game. You can play against your friend sitting next to you or against a bot. To determine where the bot should move, the project uses some APIs that perform game analysis.

## Technologies used

The project uses the following technologies:

- libraries

  - [SFML](https://www.sfml-dev.org/) — for working with graphics (and [its fork](https://github.com/Zombieschannel/SFML) that supports compilation for the Web)
  - [C++ Requests](https://docs.libcpr.org/) — for sending HTTP requests
  - [JSON for Modern C++](https://json.nlohmann.me/) — for serializing and deserializing data when saving a game or receiving game analysis from one of the chess APIs

- chess APIs

  - [StockfishOnline](https://stockfish.online/)
  - [Chess-API](https://chess-api.com/)

- tools for compilation and assembly

  - [CMake](https://cmake.org/) and [Make](https://www.gnu.org/software/make/) — as a build system
  - [Emscripten](https://emscripten.org/) — for building the project for the Web

## Downloading

The project was initially developed on Windows for Windows. Then the project underwent some refactoring, which was done on Linux. At the moment, the project can be built under Linux and Web.

To download the project, run the following commands:

```sh
git clone https://github.com/C0o1Pr0g3r/chess.git
```

## Building

To build the project, you need to go to its root directory. To do this, run the following commands:

```sh
cd chess
```

### Build for Linux

To build the project, run the following commands:

```sh
cmake -B build
cmake --build build
```

### Build for the Web

Since SFML does not support compiling for the Web, this will require some manipulation compared to compiling for Linux, so you need to meet some prerequisites, namely:

- you must have Emscripten installed
- you must have the SFML library compiled for the Web

#### Emscripten

To install Emscripten, follow [the official guide](https://emscripten.org/docs/getting_started/downloads.html).

##### Note on Emscripten programs

It is important to note that for Emscripten (_emcmake_, _emmake_ and _emrun_ programs) to work, you need to change the PATH and other environment variables in the current terminal. This is specified in the Emscripten installation instructions, so follow them if the commands given do not work.

#### SFML library compiled for the Web

To compile the SFML library for the Web, follow these instructions.

Download a fork of the SFML library that supports compilation for the Web:

```sh
git clone https://github.com/Zombieschannel/SFML.git
```

Go to the root directory of the library and switch to the desired branch:

```sh
cd SFML
git checkout SFML-3.x.x-EMCC
```

Build the library using the following commands:

```sh
emcmake cmake -B build
emmake make -C build
```

Bring the library into a state ready for use with the following command:

```sh
cmake --install build --prefix=.
```

It is important to note that in order for this project to find the SFML library compiled for the Web during build, the SFML library must be located next to this project's directory, i.e. at the same nesting level in the file system.

Once all prerequisites are met, the project can be built using the following commands (don't forget to change to the root directory of this project before running the following commands.):

```sh
emcmake cmake -B build
emmake make -C build
```

## Launch of the project

Note: the following commands must be run from the project root directory.

### On Linux

To run the project, run the following commands:

```sh
build/bin/Chess
```

### In the browser

To run the project, run the following commands:

```sh
emrun build/bin/Chess.html
```
