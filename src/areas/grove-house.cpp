#include "areas/grove-house.h"

#include "tiles/area.h"
#include "tiles/log.h"
#include "tiles/tile.h"
#include "tiles/vec.h"
#include "util/assert.h"
#include "util/compiler.h"

GroveHouse::GroveHouse() noexcept {
    scripts[StringView("open_door")] = (TileScript)&GroveHouse::onOpenDoor;
    scripts[StringView("sound_armor")] = (TileScript)&GroveHouse::armorSound;
    scripts[StringView("sound_book")] = (TileScript)&GroveHouse::bookSound;
    scripts[StringView("sound_ouch")] = (TileScript)&GroveHouse::ouchSound;
}

void
GroveHouse::onOpenDoor(Entity&) noexcept {
    if (openedDoor) {
        logErr("grove_house", "onOpenDoor called again");
        return;
    }
    openedDoor = true;

    // torch which activated this trigger should make "ouch" now
    ivec3 torch = area->grid.virt2phys(vicoord{6, 0, 0.0});
    area->grid.scripts[TileGrid::SCRIPT_TYPE_USE][torch] =
        (TileScript)&GroveHouse::ouchSound;

    // closed exit on north wall, object layer
    ivec3 door = area->grid.virt2phys(vicoord{4, 0, 0.0});
    area->grid.exits[EXIT_NORMAL][door] =
        Exit{"areas/secret_room.json", 4, 5, 0.0};
    area->grid.flags[door] &= ~TILE_NOWALK;

    TileSet* tileSet = area->getTileSet("areas/tiles/indoors.bmp");
    assert_(tileSet);

    // closed exit on north wall, graphics layer
    // change to open exit
    vicoord doorGraphic = {4, 0, -0.2};
    area->grid.setTileType(doorGraphic, tileSet->at(2, 9));

    area->requestRedraw();

    playSoundEffect("sounds/door.oga");
}

void
GroveHouse::armorSound() noexcept {
    playSoundEffect("sounds/metal_clank.oga");
}

void
GroveHouse::bookSound() noexcept {
    playSoundEffect("sounds/book.oga");
}

void
GroveHouse::ouchSound() noexcept {
    playSoundEffect("sounds/ouch.oga");
}
