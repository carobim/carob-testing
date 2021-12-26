#include "areas/big-tree.h"

BigTreeArea::BigTreeArea() noexcept {
    clouds.setZ(10.0);
}

void
BigTreeArea::onLoad() noexcept {
    clouds.createRandomCloud(*this);

    const int second = 1000;
    clouds.createCloudsRegularly(*this, 30 * second, 60 * second);
}
