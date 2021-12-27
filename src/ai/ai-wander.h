#ifndef SRC_AI_AI_WANDER_H_
#define SRC_AI_AI_WANDER_H_

// The wander AI moves characters around in a Pokemon-style fashion.  Every
// once in a while they will move in a random direction by one tile.

#include "tiles/cooldown.h"
#include "util/compiler.h"
#include "util/int.h"

class Character;

struct AIWanderTileParams {
    Character* c;
    U32 chance;
    Cooldown cooldown;
};

//! Returns a function that, given `Time dt`, will try to move the character
//! one tile every `cooldown` milliseconds.  There is a 1-in-`chance` chance
//! that the character will move during a try.
void aiWanderTile(void* params, Time dt) noexcept;

struct AIWanderTurnParams {
    Character* c;
    U32 chance;
};

//! Returns a function that will try to move the character one tile every turn.
//! There is a 1-in-`chance` chance that the character will move during a try.
void aiWanderTurn(void* params) noexcept;

#endif  // SRC_AI_AI_WANDER_H_
