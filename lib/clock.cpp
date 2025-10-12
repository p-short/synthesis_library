#include "clock.h"
#include <cmath>
#include <iostream>

namespace Sculpt {

Clock::Clock(double bpm) : m_bpm(bpm) {
    m_secondsPerBeat = 60.0 / m_bpm;
}

void Clock::SetBPM(const double newBpm) { m_bpm = newBpm; }

void Clock::Process() {
    m_totalSamples += 1.0;
}

double Clock::GetCurrentPosition() {
    // Convert total samples → seconds → beats
    double secondsElapsed = m_totalSamples / m_sampleRate;
    double beatsElapsed = secondsElapsed / m_secondsPerBeat;
    return beatsElapsed;
}

ClockFollower::ClockFollower(Clock* clockSource, const Subdivision subdivision) : m_clock(clockSource) {
    SetSubdivision(subdivision);
    m_lastTriggerBeat = m_clock->GetCurrentPosition();
}

bool ClockFollower::IsBeat() {
    if (!m_clock) return false;

    double currentBeat = m_clock->GetCurrentPosition();

    // handle wrap-around naturally (no reset needed)
    double beatDelta = currentBeat - m_lastTriggerBeat;

    if (beatDelta >= m_beatsPerTrigger) {
        // catch up for missed beats
        m_lastTriggerBeat += std::floor(beatDelta / m_beatsPerTrigger) * m_beatsPerTrigger;
        return true;
    }

    return false;
}

void ClockFollower::SetSubdivision(const Subdivision subdivision){
    m_subdivision = subdivision;
    m_beatsPerTrigger = SelectCorrectBeatDivision(subdivision);
}

double ClockFollower::SelectCorrectBeatDivision(const Subdivision subdivision) const{
    switch (subdivision) {
        case Subdivision::QUARTER_NOTE:
            return 1.0;

        case Subdivision::EIGHT_NOTE:
            return 0.5;
    }
}
} // namespace