# Tsunagari-Testing

![MIT Licensed](https://img.shields.io/github/license/TsunagariEngine/Tsunagari-Testing.svg)
[![Build Status](https://travis-ci.org/TsunagariEngine/Tsunagari-Testing.svg?branch=master)](https://travis-ci.org/TsunagariEngine/Tsunagari-Testing)
[![LoC](https://tokei.rs/b1/github/TsunagariEngine/Tsunagari-Testing)](https://github.com/Aaronepower/tokei)

A tech demo world for [Tsunagari](https://github.com/TsunagariEngine/Tsunagari).

## Setup

### Cloning

```bash
git clone --recurse-submodules https://github.com/TsunagariEngine/Tsunagari-Testing.git
cd Tsunagari-Testing
```

### Acquiring `Autumn_Forest.oga`

From the root directory:

#### Method 1: Use `youtube-dl` and `ffmpeg`

```bash
# macOS
brew install youtube-dl
brew install --with-libvorbis ffmpeg
```

```bash
cd data/music
youtube-dl -x -f 22 -o Autumn_Forest.mp4 'https://www.youtube.com/watch?v=v2qOllkxwiw'
ffmpeg -i Autumn_Forest.m4a -c:a libvorbis Autumn_Forest.oga
cd ../..
```

#### Method 2: Download from `pdm.me`

```bash
# macOS
cd data/music
curl -O https://pdm.me/Autumn_Forest.oga
cd ../..
```

```bash
# Ubuntu
cd data/music
wget https://pdm.me/Autumn_Forest.oga
cd ../..
```

### Installing build and runtime dependencies

```bash
# macOS
brew install sdl2 sdl2_image sdl2_mixer
```

```bash
# Ubuntu
sudo apt-get install cmake g++ make pkg-config libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev
```

### Building

From the root directory:

Compile:

```bash
# macOS
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug -DAV_SDL2=On
make
cd ..
```

```bash
# Ubuntu
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug -DAV_SDL2=On
make
cd ..
```

Build the resources:

```bash
Tsunagari/scripts/build-config.sh
Tsunagari/scripts/build-world.sh
```

Build the application bundle/install to bin:

```bash
# macOS
Tsunagari/scripts/build-bundle-debug.sh
```

```bash
# Ubuntu
cp build-debug/tsunagari bin/
```

### Running

#### Using a GUI file manager

On macOS, open `Tsunagari.app` in Finder.

On Ubuntu, open `bin/tsunagari` in Files.

#### Using a terminal

```bash
# macOS
Tsunagari.app/Contents/MacOS/Tsunagari
```

```bash
# Ubuntu
cd bin
./tsunagari
```

### Debugging

From the root directory:

```bash
# macOS
lldb Tsunagari.app/Contents/MacOS/Tsunagari
```

```bash
# Ubuntu
cd bin
gdb ./tsunagari
```

## TODO

- Windows instructions
