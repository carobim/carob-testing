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
    //! Create a cloud at a random position.  May do nothing if the cloud
    //! would have appeared to close to another cloud (which would be ugly).
    void createRandomCloud(DataArea* dataArea) noexcept;
    //! Create a sequence of clouds over time that drift in from the
    //! right-hand-side.  One will attempt to appear every [minMS, maxMS]
    //! milliseconds.  May do nothing if the cloud would have appeared to
    //! close to another cloud (which would be ugly).
    void createCloudsRegularly(DataArea* dataArea,
                               U32 minMS,
                               U32 maxMS) noexcept;

 public:
    //! The spawning z-height layer on which clouds will appear;
    float z;

    Vector<Overlay*> clouds;
};

#endif  // SRC_WORLD_CLOUDS_H_
