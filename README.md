# Carob Testing

![MIT Licensed](https://img.shields.io/github/license/carobim/carob.svg)
[![Build Status](https://travis-ci.org/carobim/carob.svg?branch=master)](https://travis-ci.org/carobim/carob)
[![LoC](https://tokei.rs/b1/github/carobim/carob)](https://github.com/Aaronepower/tokei)

A tech demo world for [Carob](https://github.com/carobim/carob).

## Setup

### Cloning

```bash
git clone --recurse-submodules https://github.com/carobim/carob-testing.git
cd carob-testing
```

### Acquiring `Autumn_Forest.oga`

From the root directory:

#### Method 1: Use `yt-dlp` and `ffmpeg`

```bash
# macOS
brew install yt-dlp
brew install ffmpeg
```

```bash
cd data/music
yt-dlp -x -f 22 -o Autumn_Forest.mp4 'https://www.youtube.com/watch?v=v2qOllkxwiw'
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
carob/scripts/build-config.sh
carob/scripts/build-world.sh
```

Build the application bundle/install to bin:

```bash
# macOS
carob/scripts/build-bundle-debug.sh
```

```bash
# Ubuntu
cp build-debug/carob bin/
```

### Running

#### Using a GUI file manager

On macOS, open `Carob.app` in Finder.

On Ubuntu, open `bin/carob` in Files.

#### Using a terminal

```bash
# macOS
Carob.app/Contents/MacOS/Carob
```

```bash
# Ubuntu
cd bin
./carob
```

### Debugging

From the root directory:

```bash
# macOS
lldb Carob.app/Contents/MacOS/Carob
```

```bash
# Ubuntu
cd bin
gdb ./carob
```

## TODO

- Windows instructions
