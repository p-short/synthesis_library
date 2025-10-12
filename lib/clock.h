#ifndef MUSICLANGUAGE_LIB_CLOCK_H
#define MUSICLANGUAGE_LIB_CLOCK_H

#include <memory>

namespace Sculpt {

enum class Subdivision {
    QUARTER_NOTE = 0,
    EIGHT_NOTE
};

class Clock {
public:
    Clock(double bpm);
    void SetBPM(const double newBpm);
    void Process();
    double GetCurrentPosition();

private:
    double m_bpm { 120.0 };
    const double m_sampleRate { 44100.0 };
    double m_totalSamples { 0.0 };
    double m_secondsPerBeat { 0.5 };
};

class ClockFollower {
public:
    ClockFollower(Clock* clockSource, const Subdivision subdivision);
    bool IsBeat();
    void SetSubdivision(const Subdivision subdivision);

private:
    Clock* m_clock { nullptr };
    Subdivision m_subdivision { Subdivision::QUARTER_NOTE };
    double m_lastTriggerBeat { 0.0 };
    double m_beatsPerTrigger { 1.0 }; // 1 = quarter note, 0.5 = eighth, etc.
    double SelectCorrectBeatDivision(const Subdivision subdivision) const;
};
} //namespace

#endif // MUSICLANGUAGE_LIB_CLOCK_H