#ifndef SRC_AREAS_CAVE01_H_
#define SRC_AREAS_CAVE01_H_

#include "data/data-area.h"

class Entity;

class Cave01 : public DataArea {
 public:
    Cave01() noexcept;

    void onLoad() noexcept;

	void ouchSound(Entity&) noexcept;
};

#endif  // SRC_AREAS_CAVE01_H_
