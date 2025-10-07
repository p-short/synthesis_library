#ifndef MUSICLANGUAGE_LIB_CLOCK_H
#define MUSICLANGUAGE_LIB_CLOCK_H

#include <memory>

enum class Subdivision {
    QUARTER_NOTE = 0,
    EIGHT_NOTE
};

namespace musiclib {
class Clock {
public:
    Clock(const uint32_t bpm);
    void SetBPM(const double newBpm);
    void Process(const uint32_t numberOfSamples);

    //double GetCurrentBeatPosition();

private:
    uint32_t m_bpm { 60 }; 
    uint32_t m_totalSamples {0};
    uint32_t m_interval {0};
    uint32_t next_click;
    const double m_sampleRate { 44100.0 };
};

// class ClockFollower {
// public:
//     ClockFollower(std::shared_ptr<Clock> clockSource, const Subdivision subdivision);
//     bool IsBeat();
//     void SetSubdivision(const Subdivision subdivision);

// private:
//     std::shared_ptr<Clock> m_clock { nullptr };
//     Subdivision m_subdivision { Subdivision::QUARTER_NOTE };
//     double m_lastBeat { 0.0 };
//     double m_beatDivisor { 2.0 };
//     double SelectCorrectBeatDivision(const Subdivision subdivision);
// };
} //namespace

#endif // MUSICLANGUAGE_LIB_CLOCK_H