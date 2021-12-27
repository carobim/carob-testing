#include "world/clouds.h"

#include "data/inprogress-timer.h"
#include "os/c.h"
#include "tiles/area.h"
#include "tiles/vec.h"
#include "util/compiler.h"
#include "util/int.h"
#include "util/random.h"
#include "util/string.h"

Clouds::Clouds() noexcept : z(0.0) {}

void
Clouds::setZ(float z) noexcept {
    this->z = z;
}

void
Clouds::createRandomCloud(DataArea& dataArea) noexcept {
    ivec3 areaDimensions = dataArea.area->grid.dim;

    // Random location in Area.
    vicoord tilePosition{
            randU32(0, areaDimensions.x), randU32(0, areaDimensions.y), z};

    createCloudAt(dataArea, tilePosition);
}

void
Clouds::createCloudsRegularly(DataArea& dataArea,
                              U32 minMS,
                              U32 maxMS) noexcept {
    U32 millis = randU32(minMS, maxMS);
    dataArea.add(new InProgressTimer(millis, [this, &dataArea, minMS, maxMS]() {
        ivec3 areaDimensions = dataArea.area->grid.dim;

        // Right-hand-side of the Area.
        vicoord position{areaDimensions.x + 1, randU32(0, areaDimensions.y), z};

        createCloudAt(dataArea, position);

        // Repeat.
        createCloudsRegularly(dataArea, minMS, maxMS);
    }));
}

void
Clouds::createCloudAt(DataArea& dataArea, vicoord tilePosition) noexcept {
#define SECONDS_TO_MILLISECONDS 1000.0
#define LEFT -1
// #define RIGHT 1

    ivec2 tileDimensions = dataArea.area->grid.tileDim;

    fvec3 pixelPosition{
            static_cast<float>(static_cast<I64>(tilePosition.x) *
                               static_cast<I64>(tileDimensions.x)),
            static_cast<float>(static_cast<I64>(tilePosition.y) *
                               static_cast<I64>(tileDimensions.y)),
            10.0};

    float minimumAcceptableDistance =
            static_cast<float>(static_cast<I64>(tileDimensions.x) * 8);

    for (Overlay* other : clouds) {
        fvec3 otherPosition = other->getPixelCoord();
        float dist = distanceTo(pixelPosition, otherPosition);
        if (dist < minimumAcceptableDistance) {
            return;
        }
    }

    String type = String("entities/clouds/cloud") << randU32(1, 4) << ".json";
    Overlay* cloud =
            dataArea.area->spawnOverlay(type, tilePosition, "stance");

    clouds.push(cloud);

    ivec2 cloudSize = cloud->getImageSize();  // in pixels
    I32 cloudWidthInTiles =
            static_cast<I32>(ceilf(static_cast<float>(cloudSize.x) /
                                  static_cast<float>(tileDimensions.x)));

    // Drift just enough to get off screen.
    I32 tilesToDrift = LEFT * (tilePosition.x + cloudWidthInTiles);
    ivec2 drift{tilesToDrift * tileDimensions.x, 0};

    I32 driftDuration =
            static_cast<I32>((drift.x < 0 ? -drift.x : drift.x) /
                             cloud->getSpeedInPixels() * SECONDS_TO_MILLISECONDS);

    cloud->drift(ivec2{drift.x, 0});
    dataArea.add(new InProgressTimer(driftDuration, [this, cloud]() {
        cloud->destroy();

        for (Size i = 0; i < clouds.size; i++) {
            if (clouds[i] == cloud) {
                clouds.erase(i);
                break;
            }
        }
    }));
}
