#include "ai/ai-wander.h"

#include "tiles/character.h"
#include "tiles/client-conf.h"
#include "tiles/vec.h"
#include "util/assert.h"
#include "util/compiler.h"
#include "util/int.h"
#include "util/random.h"

static ivec2
randomFacing() noexcept {
    switch (randU32(0, 3)) {
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
maybeMove(Character* c, U32 chance) noexcept {
    if (randU32(1, chance) == 1) {
        // doMove(c.lock());
        doMove(c);
    }
    else if (randU32(1, chance) == 1) {
        // doFace(c.lock());
        doFace(c);
    }
}

void
aiWanderTile(void* params_, Time dt) noexcept {
    AIWanderTileParams* params = static_cast<AIWanderTileParams*>(params_);

    assert_(confMoveMode == MoveMode::TILE);

    params->cooldown.advance(dt);
    if (params->cooldown.hasExpired()) {
        params->cooldown.wrapAll();
        maybeMove(params->c, params->chance);
    };
}

void
aiWanderTurn(void* params_) noexcept {
    AIWanderTurnParams* params = static_cast<AIWanderTurnParams*>(params_);

    assert_(confMoveMode == MoveMode::TURN);

    maybeMove(params->c, params->chance);
}
