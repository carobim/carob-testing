#include "ai/ai-wander.h"

#include "tiles/character.h"
#include "tiles/client-conf.h"
#include "tiles/cooldown.h"
#include "util/assert.h"
#include "util/random.h"

static ivec2
randomFacing() noexcept {
    switch (randInt(0, 3)) {
    case 0:
        return {-1, 0};
    case 1:
        return {+1, 0};
    case 2:
        return {0, -1};
    case 3:
        return {0, +1};
    }
    return {0, 0};
}

//! Move the character.
static void
doMove(Character* c) noexcept {
    c->moveByTile(randomFacing());
}

//! Change direction we are facing.
static void
doFace(Character* c) noexcept {
    c->setFacing(randomFacing());
    c->setAnimationStanding();
}

//! Decide whether or not to move.
static void
maybeMove(Character* c, int chance) noexcept {
    if (randInt(1, chance) == 1) {
        // doMove(c.lock());
        doMove(c);
    }
    else if (randInt(1, chance) == 1) {
        // doFace(c.lock());
        doFace(c);
    }
}

Function<void(time_t)>
AIWanderTile(Character* c, int chance, time_t tryEvery) noexcept {
    assert_(confMoveMode == MoveMode::TILE);

    Cooldown cooldown(tryEvery);
    return [c, chance, cooldown](time_t dt) mutable {
        cooldown.advance(dt);
        if (cooldown.hasExpired()) {
            cooldown.wrapAll();
            maybeMove(c, chance);
        }
    };
}

Function<void()>
AIWanderTurn(Character* c, int chance) noexcept {
    assert_(confMoveMode == MoveMode::TURN);

    return [c, chance]() mutable { maybeMove(c, chance); };
}
