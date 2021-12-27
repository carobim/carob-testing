#include "areas/grove01.h"

#include "ai/ai-wander.h"
#include "data/action.h"
#include "data/data-area.h"
#include "os/c.h"
#include "tiles/area.h"
#include "tiles/entity.h"
#include "tiles/log.h"
#include "tiles/music.h"
#include "tiles/npc.h"
#include "util/compiler.h"
#include "util/int.h"
#include "util/new.h"
#include "world/clouds.h"

static Clouds clouds;

static bool drinking = false;

static bool openedChest = false;
static bool musicPaused = false;

// Circular in-out ease
static float
ease(float x) noexcept {
    return 0.5f * sinf(M_PI * x - M_PI / 2.0f) + 0.5f;
}

static void
wash(DataArea* area, void*, float progress) noexcept {
#define MAX_ALPHA 192
    U8 alpha;

    if (progress < 0.5f) {
        alpha = static_cast<U8>(MAX_ALPHA * ease(2.0f * progress));
    }
    else if (progress < 1.0f) {
        alpha = static_cast<U8>(MAX_ALPHA * ease(2.0f * (1.0f - progress)));
    }
    else {
        alpha = 0.0f;
        drinking = false;
    }

    area->area->setColorOverlay(alpha, 255, 255, 255);
}

static void
onWell(DataArea* area, Entity*, ivec3) noexcept {
    if (drinking) {
        return;
    }

    drinking = true;

    playSoundEffect("sounds/splash.oga");

    struct Action delay = makeDelayAction(1000);

    delay.next = xmalloc(struct Action, 1);
    *delay.next = makeTimerAction(1000, wash, 0, 0);

    area->add(delay);
}

static void
toggleMusic() noexcept {
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

static void
onOpenChest(DataArea* area, Entity*, ivec3) noexcept {
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

    TileSet* objects = area->area->getTileSet("areas/tiles/objects.bmp");

    // Change to closed chest to open chest. Bottom and top halves.
    area->area->grid.setTileType(vicoord{5, 20, -0.1}, objects->at(1, 5));
    area->area->grid.setTileType(vicoord{5, 21, -0.1}, objects->at(1, 6));
    area->area->requestRedraw();

    playSoundEffect("sounds/door.oga");
}

Grove01::Grove01() noexcept {
    clouds.z = 10.0;

    scripts.allocate(hash_(StringView("well"))) = onWell;
    scripts.allocate(hash_(StringView("open_chest"))) = onOpenChest;
}

void
Grove01::onLoad() noexcept {
    // Create a wandering wizard NPC.
    Character* wizard = area->spawnNPC(
            "entities/wizard/wizard.json", vicoord{16, 22, 0.0}, "down");

    // Make it move.
    new2(AIWanderTileParams, params, c, wizard, chance, 4);
    new (&params->cooldown) Cooldown(1000);

    make2(Entity::OnTickFn, fn, fn, aiWanderTile, data, params);
    wizard->attach(fn);

    // And a few drifting cloud Overlays.
    for (int i = 0; i < 5; i++) {
        clouds.createRandomCloud(this);
    }

#define SECOND 1000
    clouds.createCloudsRegularly(this, 10 * SECOND, 20 * SECOND);
}
