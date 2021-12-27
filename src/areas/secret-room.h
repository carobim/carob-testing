#ifndef SRC_AREAS_SECRET_ROOM_H_
#define SRC_AREAS_SECRET_ROOM_H_

#include "data/data-area.h"
#include "util/compiler.h"

class SecretRoom : public DataArea {
 public:
    SecretRoom() noexcept;
};

#endif  // SRC_AREAS_SECRET_ROOM_H_
