#include "areas/grove01.h"

#include "ai/ai-wander.h"
#include "data/inprogress-timer.h"
#include "tiles/area.h"
#include "tiles/log.h"
#include "tiles/music.h"
#include "tiles/npc.h"

// Circular in-out ease
static double
ease(double x) noexcept {
    return 0.5 * sin(M_PI * x - M_PI / 2) + 0.5;
}

Grove01::Grove01() noexcept {
    clouds.setZ(10.0);

    scripts[StringView("well")] = (TileScript)&Grove01::onWell;
    scripts[StringView("open_chest")] = (TileScript)&Grove01::onOpenChest;
}

void
Grove01::onLoad() noexcept {
    // Create a wandering wizard NPC.
    Character* wizard = area->spawnNPC(
            "entities/wizard/wizard.json", vicoord{16, 22, 0.0}, "down");
    wizard->attach(AIWanderTile(wizard, 4, 1000));

    // And a few drifting cloud Overlays.
    for (int i = 0; i < 5; i++) {
        clouds.createRandomCloud(*this);
    }

    const int second = 1000;
    clouds.createCloudsRegularly(*this, 10 * second, 20 * second);
}

void
Grove01::onWell(Entity&) noexcept {
    const int maxAlpha = 192;

    if (drinking) {
        return;
    }

    drinking = true;

    playSoundEffect("sounds/splash.oga");

    add(new InProgressTimer(
            1000,
            [this, maxAlpha](double percent) {
                uint8_t alpha;
                if (percent < 0.5) {
                    alpha = (uint8_t)(maxAlpha * ease(2 * percent));
                }
                else {
                    alpha = (uint8_t)(maxAlpha * ease(2 * (1 - percent)));
                }
                area->setColorOverlay(alpha, 255, 255, 255);
            },
            [this, maxAlpha]() {
                area->setColorOverlay(0, 0, 0, 0);
                drinking = false;
            }));
}

void
Grove01::onOpenChest(Entity&) noexcept {
    /* This function is called when the chest in grove01.json is
     * activated by the player. The first time we are run, we open
     * the chest.  Further invocations feature an easter egg where
     * we toggle the game's music. :)
     */

    if (openedChest) {
        toggleMusic();
        return;
    }

    openedChest = true;

    auto objects = area->getTileSet("areas/tiles/objects.bmp");

    // Change to closed chest to open chest. Bottom and top halves.
    area->grid.setTileType(vicoord{5, 20, -0.1}, objects->at(1, 5));
    area->grid.setTileType(vicoord{5, 21, -0.1}, objects->at(1, 6));
    area->requestRedraw();

    playSoundEffect("sounds/door.oga");
}

void
Grove01::toggleMusic() noexcept {
    if (musicPaused) {
        musicResume();
        logInfo("grove01", "Unpausing music!");
    }
    else {
        musicPause();
        logInfo("grove01", "Pausing music!");
    }
    musicPaused = !musicPaused;
}
