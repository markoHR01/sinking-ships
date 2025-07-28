# Sinking Ships (video game) (client)

**Video game client, written in C++. Inspired by Battleships (1967).**

## How to Build (UNIX)

### 1. Install Dependencies

You can use `g++`, `make` and the SDL2 library to build the client:

```bash
sudo pacman -Syu base-devel sdl2 sdl2_ttf
```

### 2. Make and Run

To build the code, simply run `make`:

```bash
make && ./sinking-ships
```

## How to Build (WINDOWS)

### 1. Install Dependencies

You can build the project using [mingw-w64](https://www.mingw-w64.org/downloads/):
- Architecture: `x86_64`
- Threads: `posix`

Add `bin` folder (i.e. `C:\mingw64\bin`) to your `PATH` and verify installation:

```powershell
g++ --version
```

You can download the SDL2 libraries from here:
- [SDL2](https://www.github.com/libsdl-org/SDL/releases)
- [SDL2\_ttf](https://www.github.com/libsdl-org/SDL_ttf/releases)

Extract the contents of `x86_64` folder (`bin/`, `include/`, `lib/`) to:
- C:\\dev\\libs\\SDL2
- C:\\dev\\libs\\SDL2\_ttf

Alternatively, modify `SDL2_DIR` and `SDL2_TTF_DIR` inside the `build.bat` file.

### 2. Build and Run

To build the code, simply run the `build.bat` file:

```powershell
.\build.bat && .\sinking-ships.exe
```
