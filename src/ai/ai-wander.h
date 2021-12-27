#ifndef SRC_AI_AI_WANDER_H_
#define SRC_AI_AI_WANDER_H_

// The wander AI moves characters around in a Pokemon-style fashion.  Every
// once in a while they will move in a random direction by one tile.

#include "util/compiler.h"
#include "util/function.h"
#include "util/int.h"

class Character;

//! Returns a function that, given `time_t dt`, will try to move the character
//! one tile every `tryEvery` milliseconds.  There is a 1-in-`chance` chance
//! that the character will move during a try.
Function<void(Time)> AIWanderTile(Character* c,
                                    U32 chance,
                                    Time tryEvery) noexcept;

//! Returns a function that will try to move the character one tile every turn.
//! There is a 1-in-`chance` chance that the character will move during a try.
Function<void()> AIWanderTurn(Character* c, U32 chance) noexcept;

#endif  // SRC_AI_AI_WANDER_H_
