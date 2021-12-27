#ifndef SRC_AREAS_GROVE_HOUSE_H_
#define SRC_AREAS_GROVE_HOUSE_H_

#include "data/data-area.h"
#include "util/compiler.h"

class Entity;

class GroveHouse : public DataArea {
    bool openedDoor = false;

 public:
    GroveHouse() noexcept;

    void onOpenDoor(Entity&) noexcept;
    void armorSound() noexcept;
    void bookSound() noexcept;
    void ouchSound() noexcept;
};

#endif  // SRC_AREAS_GROVE_HOUSE_H_
