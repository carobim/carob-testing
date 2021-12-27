#ifndef SRC_AREAS_GROVE01_H_
#define SRC_AREAS_GROVE01_H_

#include "data/data-area.h"
#include "util/compiler.h"

class Grove01 : public DataArea {
 public:
    Grove01() noexcept;

    void onLoad() noexcept;
};

#endif  // SRC_AREAS_GROVE01_H_
