#include "areas/cave01.h"

#include "data/action.h"
#include "tiles/area.h"
#include "tiles/player.h"
#include "util/compiler.h"
#include "util/int.h"

/*
#include <future>

class DataExpr {
 public:
    virtual std::future<void> operator()() = 0;

 protected:
    DataExpr() = default;
    virtual ~DataExpr() = default;

 private:
    DataExpr& operator=(const DataExpr&);
};


struct TimelineItem {
    time_t start;
    Unique<DataExpr> expr;
};

typedef vector<TimelineItem> Timeline;


class SetPlayerFreezeExpr : public DataExpr {};
class SetPlayerPhaseExpr : public DataExpr {};
class FadeOutExpr : public DataExpr {};
class PlaySoundExpr : public DataExpr {};
class FadeInExpr : public DataExpr {};

class TimelineExec {
 public:
    void tick(time_t dt);
    void turn();

 private:
   time_t timeRunSoFar;
};
*/

static void
fadeIn(DataArea*, void* data, float progress) noexcept {
    fromCast(Area, area, data);

    if (progress < 1.0) {
        U8 alpha = static_cast<U8>(255 - progress * 255);
        area->setColorOverlay(alpha, 0, 0, 0);
    }
    else {
        area->setColorOverlay(0, 0, 0, 0);
        player.setFrozen(false);
    }
}

static void
ouchSound(DataArea*, Entity*, ivec3) noexcept {
    playSoundEffect("sounds/ouch.oga");
}

Cave01::Cave01() noexcept {
    scripts.allocate(hash_(StringView("sound_ouch"))) = ouchSound;
}

void
Cave01::onLoad() noexcept {
    /*
    run(Timeline{
        {    0, new SetPlayerFreeze(true) },
        {    0, new SetPlayerPhase("up") },
        {    0, new FadeOut({0, 0, 0}, 0) },
        {    0, new PlaySound("sounds/rockfall.oga") },
        { 5000, new FadeIn(3000) },
        { 8000, new SetPlayerFreeze(false) }
    });
    */

    player.setFrozen(true);
    player.setPhase("up");
    area->setColorOverlay(255, 0, 0, 0);

    struct Action sound = makeSoundAction("sounds/rockfall.oga");

    sound.next = xmalloc(struct Action, 1);
    *sound.next = makeTimerAction(3000, fadeIn, area, 0);

    add(sound);
}
