#ifndef SRC_AREAS_GROVE01_H_
#define SRC_AREAS_GROVE01_H_

#include "data/data-area.h"
#include "util/compiler.h"
#include "world/clouds.h"

class Entity;

class Grove01 : public DataArea {
    Clouds clouds;

    bool drinking = false;

    bool openedChest = false;
    bool musicPaused = false;

 public:
    Grove01() noexcept;

    void onLoad() noexcept;

    void onWell(Entity&) noexcept;
    void onOpenChest(Entity&) noexcept;
    void toggleMusic() noexcept;
};

#endif  // SRC_AREAS_GROVE01_H_
