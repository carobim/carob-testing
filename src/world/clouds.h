#ifndef SRC_WORLD_CLOUDS_H_
#define SRC_WORLD_CLOUDS_H_

#include "tiles/overlay.h"
#include "tiles/vec.h"
#include "util/compiler.h"
#include "util/int.h"
#include "util/vector.h"

class DataArea;

//! Create clouds that drift left across an Area.
class Clouds {
 public:
    Clouds() noexcept;

    //! Set spawning z-height layer that clouds will appear on.
    void setZ(float z) noexcept;

    //! Create a cloud at a random position.  May do nothing if the cloud
    //! would have appeared to close to another cloud (which would be ugly).
    void createRandomCloud(DataArea& dataArea) noexcept;
    //! Create a sequence of clouds over time that drift in from the
    //! right-hand-side.  One will attempt to appear every [minMS, maxMS]
    //! milliseconds.  May do nothing if the cloud would have appeared to
    //! close to another cloud (which would be ugly).
    void createCloudsRegularly(DataArea& dataArea,
                               U32 minMS,
                               U32 maxMS) noexcept;

 private:
    //! Create a cloud, move it left until out of area, then destroy it.
    //! If the cloud would be created next to another, already existing
    //! cloud, do nothing.
    void createCloudAt(DataArea& dataArea, vicoord tilePosition) noexcept;

    float z;

    Vector<Overlay*> clouds;
};

#endif  // SRC_WORLD_CLOUDS_H_
