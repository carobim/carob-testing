#include "world/clouds.h"

#include "data/inprogress-timer.h"
#include "tiles/area.h"
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
            randInt(0, areaDimensions.x), randInt(0, areaDimensions.y), z};

    createCloudAt(dataArea, tilePosition);
}

void
Clouds::createCloudsRegularly(DataArea& dataArea,
                              int minMS,
                              int maxMS) noexcept {
    int millis = randInt(minMS, maxMS);
    dataArea.add(new InProgressTimer(millis, [this, &dataArea, minMS, maxMS]() {
        ivec3 areaDimensions = dataArea.area->grid.dim;

        // Right-hand-side of the Area.
        vicoord position{areaDimensions.x + 1, randInt(0, areaDimensions.y), z};

        createCloudAt(dataArea, position);

        // Repeat.
        createCloudsRegularly(dataArea, minMS, maxMS);
    }));
}

void
Clouds::createCloudAt(DataArea& dataArea, vicoord tilePosition) noexcept {
    const float secondsToMilliseconds = 1000.0;
    const int left = -1;
    // const int right = 1;

    ivec2 tileDimensions = dataArea.area->grid.tileDim;

    fvec3 pixelPosition{
            static_cast<float>(static_cast<int64_t>(tilePosition.x) *
                               static_cast<int64_t>(tileDimensions.x)),
            static_cast<float>(static_cast<int64_t>(tilePosition.y) *
                               static_cast<int64_t>(tileDimensions.y)),
            10.0};

    const float minimumAcceptableDistance =
            static_cast<float>(static_cast<int64_t>(tileDimensions.x) * 8);

    for (auto& other : clouds) {
        fvec3 otherPosition = other->getPixelCoord();
        float dist = distanceTo(pixelPosition, otherPosition);
        if (dist < minimumAcceptableDistance) {
            return;
        }
    }

    String type = String("entities/clouds/cloud") << randInt(1, 4) << ".json";
    Overlay* cloud =
            dataArea.area->spawnOverlay(type, tilePosition, "stance");

    clouds.push_back(cloud);

    ivec2 cloudSize = cloud->getImageSize();  // in pixels
    int cloudWidthInTiles =
            static_cast<int>(ceil(static_cast<float>(cloudSize.x) /
                                  static_cast<float>(tileDimensions.x)));

    // Drift just enough to get off screen.
    int tilesToDrift = left * (tilePosition.x + cloudWidthInTiles);
    ivec2 drift{tilesToDrift * tileDimensions.x, 0};

    int driftDuration =
            static_cast<int>((drift.x < 0 ? -drift.x : drift.x) /
                             cloud->getSpeedInPixels() * secondsToMilliseconds);

    cloud->drift(ivec2{drift.x, 0});
    dataArea.add(new InProgressTimer(driftDuration, [this, cloud]() {
        cloud->destroy();

        for (size_t i = 0; i < clouds.size; i++) {
            if (clouds[i] == cloud) {
                clouds.erase(i);
                break;
            }
        }
    }));
}
