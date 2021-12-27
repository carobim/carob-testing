#include "areas/big-tree.h"

#include "util/compiler.h"
#include "world/clouds.h"

static Clouds clouds;

BigTreeArea::BigTreeArea() noexcept {
    clouds.z = 10.0;
}

void
BigTreeArea::onLoad() noexcept {
    clouds.createRandomCloud(this);

#define SECOND 1000
    clouds.createCloudsRegularly(this, 30 * SECOND, 60 * SECOND);
}
