#include "areas/grove04.h"

Grove04::Grove04() noexcept {
    clouds.setZ(10.0);
}

void
Grove04::onLoad() noexcept {
    clouds.createRandomCloud(*this);

    const int second = 1000;
    clouds.createCloudsRegularly(*this, 20 * second, 30 * second);
}
