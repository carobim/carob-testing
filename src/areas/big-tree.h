#ifndef SRC_AREAS_BIG_TREE_H_
#define SRC_AREAS_BIG_TREE_H_

#include "data/data-area.h"
#include "util/compiler.h"
#include "world/clouds.h"

class BigTreeArea : public DataArea {
    Clouds clouds;

 public:
    BigTreeArea() noexcept;

    void onLoad() noexcept;
};

#endif  // SRC_AREAS_BIG_TREE_H_
