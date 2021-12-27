#ifndef SRC_AREAS_GROVE06_H_
#define SRC_AREAS_GROVE06_H_

#include "data/data-area.h"
#include "util/compiler.h"

class Grove06 : public DataArea {
 public:
    Grove06() noexcept;

    void onLoad() noexcept;
};

#endif  // SRC_AREAS_GROVE06_H_
