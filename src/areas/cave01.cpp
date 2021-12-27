#include "areas/cave01.h"

#include "data/inprogress-sound.h"
#include "data/inprogress-timer.h"
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

Cave01::Cave01() noexcept {
    scripts[StringView("sound_ouch")] = (TileScript)&Cave01::ouchSound;
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

    Player& player = Player::instance();
    player.setFrozen(true);
    player.setPhase("up");
    area->setColorOverlay(255, 0, 0, 0);

    add(new InProgressSound("sounds/rockfall.oga", [this]() {
        add(new InProgressTimer(
                3000,
                [this](float percent) {
                    U8 alpha = static_cast<U8>(255 - percent * 255);
                    area->setColorOverlay(alpha, 0, 0, 0);
                },
                [this]() {
                    area->setColorOverlay(0, 0, 0, 0);
                    Player::instance().setFrozen(false);
                }));
    }));
}

void
Cave01::ouchSound(Entity&) noexcept {
    playSoundEffect("sounds/ouch.oga");
}
