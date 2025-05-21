#include "world/clouds.h"

#include "data/action.h"
#include "data/data-area.h"
#include "os/c.h"
#include "tiles/area.h"
#include "tiles/vec.h"
#include "util/compiler.h"
#include "util/int.h"
#include "util/new.h"
#include "util/random.h"
#include "util/string.h"

struct DestroyCloudParams {
    Clouds* clouds;
    Overlay* cloud;
};

static void
destroyCloud(DataArea*, void* data) noexcept {
    fromCast(struct DestroyCloudParams, params, data);

    params->cloud->destroy();

    for (Size i = 0; i < params->clouds->clouds.size; i++) {
        if (params->clouds->clouds[i] == params->cloud) {
            params->clouds->clouds.erase(i);
            break;
        }
    }
}

//! Create a cloud, move it left until out of area, then destroy it.
//! If the cloud would be created next to another, already existing
//! cloud, do nothing.
static void
createCloudAt(Clouds* clouds,
              DataArea* dataArea,
              vicoord tilePosition) noexcept {
#define SECONDS_TO_MILLISECONDS 1000.0
#define LEFT -1
    // #define RIGHT 1

    ivec2 tileDimensions = dataArea->area->grid.tileDim;

    fvec3 pixelPosition;
    pixelPosition.x = static_cast<float>(static_cast<I64>(tilePosition.x) *
                                         static_cast<I64>(tileDimensions.x));
    pixelPosition.y = static_cast<float>(static_cast<I64>(tilePosition.y) *
                                         static_cast<I64>(tileDimensions.y));
    pixelPosition.z = 10.0;

    float minimumAcceptableDistance =
            static_cast<float>(static_cast<I64>(tileDimensions.x) * 8);

    for (Size i = 0; i < clouds->clouds.size; i++) {
        Overlay* other = clouds->clouds.data[i];
        fvec3 otherPosition = other->getPixelCoord();
        float dist = distanceTo(pixelPosition, otherPosition);
        if (dist < minimumAcceptableDistance) {
            return;
        }
    }

    String type = String("entities/clouds/cloud") << randU32(1, 4) << ".json";
    Overlay* cloud = dataArea->area->spawnOverlay(type, tilePosition, "stance");

    clouds->clouds.push(cloud);

    ivec2 cloudSize = cloud->getImageSize();  // in pixels
    I32 cloudWidthInTiles =
            static_cast<I32>(ceilf(static_cast<float>(cloudSize.x) /
                                   static_cast<float>(tileDimensions.x)));

    // Drift just enough to get off screen.
    I32 tilesToDrift = LEFT * (tilePosition.x + cloudWidthInTiles);
    ivec2 drift;
    drift.x = tilesToDrift * tileDimensions.x;
    drift.y = 0;

    I32 driftDuration = static_cast<I32>((drift.x < 0 ? -drift.x : drift.x) /
                                         cloud->getSpeedInPixels() *
                                         SECONDS_TO_MILLISECONDS);

    ivec2 v;
    v.x = drift.x;
    v.y = 0;
    cloud->drift(v);

    struct Action delay = makeDelayAction(driftDuration);

    new2(struct DestroyCloudParams, params, clouds, clouds, cloud, cloud);
    delay.next = xmalloc(struct Action, 1);
    *delay.next = makeUnitAction(destroyCloud, params, free);

    dataArea->add(delay);
}

struct OffscreenCloudParams {
    Clouds* clouds;
    U32 minMS;
    U32 maxMS;
};

static void
createOffscreenCloud(DataArea* area, void* data) noexcept {
    fromCast(struct OffscreenCloudParams, params, data);

    ivec3 areaDimensions = area->area->grid.dim;

    // Right-hand-side of the Area.
    vicoord position;
    position.x = areaDimensions.x + 1;
    position.y = randU32(0, areaDimensions.y);
    position.z = params->clouds->z;

    createCloudAt(params->clouds, area, position);

    // Repeat.
    params->clouds->createCloudsRegularly(area, params->minMS, params->maxMS);
}

void
Clouds::createRandomCloud(DataArea* dataArea) noexcept {
    ivec3 areaDimensions = dataArea->area->grid.dim;

    // Random location in Area.
    vicoord tilePosition;
    tilePosition.x = randU32(0, areaDimensions.x);
    tilePosition.y = randU32(0, areaDimensions.y);
    tilePosition.z = z;

    createCloudAt(this, dataArea, tilePosition);
}

void
Clouds::createCloudsRegularly(DataArea* dataArea,
                              U32 minMS,
                              U32 maxMS) noexcept {
    U32 millis = randU32(minMS, maxMS);

    struct Action delay = makeDelayAction(millis);

    new0(OffscreenCloudParams, params);
    params->clouds = this;
    params->minMS = minMS;
    params->maxMS = maxMS;
    delay.next = xmalloc(struct Action, 1);
    *delay.next = makeUnitAction(createOffscreenCloud, params, free);

    dataArea->add(delay);
}
