#include "areas/big-tree.h"

#include "util/compiler.h"

BigTreeArea::BigTreeArea() noexcept {
    clouds.setZ(10.0);
}

void
BigTreeArea::onLoad() noexcept {
    clouds.createRandomCloud(*this);

#define SECOND 1000
    clouds.createCloudsRegularly(*this, 30 * SECOND, 60 * SECOND);
}
