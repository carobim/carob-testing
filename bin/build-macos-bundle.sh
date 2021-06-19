#!/bin/sh

help() {
    echo 'Usage: build-macos-bundle.sh BUILD_DIR'
}

if [ $# = 0 ] || ! [ $# = 1 ] || [ "$1" = '-h' -o "$1" = '--help' ]; then
    help
    exit 0
fi

build="$1"

testing="${0%/*}/.."

"$testing"/Tsunagari/bin/build-macos-bundle.sh "$build" testing \
                                               'Tsunagari Engine' data \
                                               testing.world
