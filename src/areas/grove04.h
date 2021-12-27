#ifndef SRC_AREAS_GROVE04_H_
#define SRC_AREAS_GROVE04_H_

#include "data/data-area.h"
#include "util/compiler.h"
#include "world/clouds.h"

class Grove04 : public DataArea {
    Clouds clouds;

 public:
    Grove04() noexcept;

    void onLoad() noexcept;
};

#endif  // SRC_AREAS_GROVE04_H_
