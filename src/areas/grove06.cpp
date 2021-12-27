#include "areas/grove06.h"

#include "util/compiler.h"
#include "world/clouds.h"

static Clouds clouds;

Grove06::Grove06() noexcept {
    clouds.z = 10.0;
}

void
Grove06::onLoad() noexcept {
    clouds.createRandomCloud(this);

#define SECOND 1000
    clouds.createCloudsRegularly(this, 20 * SECOND, 30 * SECOND);
}
