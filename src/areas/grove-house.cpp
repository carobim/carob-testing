#include "areas/grove-house.h"

#include "tiles/area.h"
#include "tiles/log.h"
#include "tiles/tile.h"
#include "tiles/vec.h"
#include "util/assert.h"
#include "util/compiler.h"

static bool openedDoor = false;

static void
armorSound(DataArea*, Entity*, ivec3) noexcept {
    playSoundEffect("sounds/metal_clank.oga");
}

static void
bookSound(DataArea*, Entity*, ivec3) noexcept {
    playSoundEffect("sounds/book.oga");
}

static void
ouchSound(DataArea*, Entity*, ivec3) noexcept {
    playSoundEffect("sounds/ouch.oga");
}

static void
onOpenDoor(DataArea* area, Entity*, ivec3) noexcept {
    if (openedDoor) {
        logErr("grove_house", "onOpenDoor called again");
        return;
    }
    openedDoor = true;

    // torch which activated this trigger should make "ouch" now
    vicoord coord;
    coord.x = 6;
    coord.y = 0;
    coord.z = 0.0;
    ivec3 torch = area->area->grid.virt2phys(coord);
    area->area->grid.scripts[TileGrid::SCRIPT_TYPE_USE][torch] = ouchSound;

    // closed exit on north wall, object layer
    coord.x = 4;
    coord.y = 0;
    coord.z = 0.0;
    ivec3 door = area->area->grid.virt2phys(coord);
    Exit exit;
    exit.area = "areas/secret_room.json";
    exit.coords.x = 4;
    exit.coords.y = 5;
    exit.coords.z = 0.0;
    area->area->grid.exits[EXIT_NORMAL][door] = exit;
    area->area->grid.flags[door] &= ~TILE_NOWALK;

    TileSet* tileSet = area->area->getTileSet("areas/tiles/indoors.bmp");
    assert_(tileSet);

    // closed exit on north wall, graphics layer
    // change to open exit
    vicoord doorGraphic = {4, 0, -0.2};
    area->area->grid.setTileType(doorGraphic, tileSet->at(2, 9));

    area->area->requestRedraw();

    playSoundEffect("sounds/door.oga");
}

GroveHouse::GroveHouse() noexcept {
    scripts.allocate(hash_(StringView("open_door"))) = onOpenDoor;
    scripts.allocate(hash_(StringView("sound_armor"))) = armorSound;
    scripts.allocate(hash_(StringView("sound_book"))) = bookSound;
    scripts.allocate(hash_(StringView("sound_ouch"))) = ouchSound;
}
