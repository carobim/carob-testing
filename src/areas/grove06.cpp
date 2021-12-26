#include "areas/grove06.h"

Grove06::Grove06() noexcept {
    clouds.setZ(10.0);
}

void
Grove06::onLoad() noexcept {
    clouds.createRandomCloud(*this);

    const int second = 1000;
    clouds.createCloudsRegularly(*this, 20 * second, 30 * second);
}
