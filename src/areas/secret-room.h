#ifndef SRC_AREAS_SECRET_ROOM_H_
#define SRC_AREAS_SECRET_ROOM_H_

#include "data/data-area.h"

class SecretRoom : public DataArea {
 public:
    SecretRoom() noexcept;

    void bookSound() noexcept;
    void ouchSound() noexcept;
};

#endif  // SRC_AREAS_SECRET_ROOM_H_
