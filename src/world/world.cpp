/***************************************
** Tsunagari Tile Engine              **
** world.cpp                          **
** Copyright 2014      Michael Reiley **
** Copyright 2014-2020 Paul Merrill   **
***************************************/

// **********
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// **********

#include "world/world.h"

#include "areas/big-tree.h"
#include "areas/cave01.h"
#include "areas/grove-house.h"
#include "areas/grove01.h"
#include "areas/grove04.h"
#include "areas/grove06.h"
#include "areas/secret-room.h"
#include "core/log.h"
#include "util/hashtable.h"
#include "util/string.h"

static Hashmap<String, DataArea*> areas;

StringView DataWorld::name = "Testing World";
StringView DataWorld::author = "Michael Reiley and Paul Merrill";
StringView DataWorld::version = "1";

enum Conf::MovementMode DataWorld::moveMode = Conf::TILE;
rvec2 DataWorld::viewportResolution = {240, 160};
int DataWorld::inputPersistDelayInitial = 300;
int DataWorld::inputPersistDelayConsecutive = 100;
StringView DataWorld::startArea = "areas/grove01.json";
StringView DataWorld::playerFile = "entities/player/player.json";
StringView DataWorld::playerStartPhase = "down";
vicoord DataWorld::startCoords = {15, 22, 0.0};

StringView DataWorld::datafile = "./testing.world";

bool
DataWorld::init() noexcept {
    areas["areas/basement.json"] = new DataArea;  // no special logic
    areas["areas/bigtree.json"] = new BigTreeArea;
    areas["areas/cave01.json"] = new Cave01;
    areas["areas/grove_house.json"] = new GroveHouse;
    areas["areas/grove01.json"] = new Grove01;
    areas["areas/grove04.json"] = new Grove04;
    areas["areas/grove06.json"] = new Grove06;
    areas["areas/secret_room.json"] = new SecretRoom;
    logInfo("TestingDataWorld", "Ready to go");
    return true;
}

DataArea*
DataWorld::area(StringView areaName) noexcept {
    return areas[areaName];
}
