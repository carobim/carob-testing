#include "areas/secret-room.h"

#include "util/compiler.h"
#include "util/string-view.h"

static void
bookSound(DataArea*, Entity*, ivec3) noexcept {
    playSoundEffect("sounds/book.oga");
}

static void
ouchSound(DataArea*, Entity*, ivec3) noexcept {
    playSoundEffect("sounds/ouch.oga");
}

SecretRoom::SecretRoom() noexcept {
    scripts.allocate(hash_(StringView("sound_book"))) = bookSound;
    scripts.allocate(hash_(StringView("sound_ouch"))) = ouchSound;
}
