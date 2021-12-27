#include "areas/secret-room.h"

#include "util/compiler.h"
#include "util/string-view.h"

SecretRoom::SecretRoom() noexcept {
    scripts[StringView("sound_book")] = (TileScript)&SecretRoom::bookSound;
    scripts[StringView("sound_ouch")] = (TileScript)&SecretRoom::ouchSound;
}

void
SecretRoom::bookSound() noexcept {
    playSoundEffect("sounds/book.oga");
}

void
SecretRoom::ouchSound() noexcept {
    playSoundEffect("sounds/ouch.oga");
}
