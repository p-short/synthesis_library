#include "clock.h"
#include <iostream>

// TODO: fix clock class, not working as expected
namespace musiclib {
Clock::Clock(const uint32_t bpm) {
    m_bpm = bpm;
    m_interval = static_cast<uint32_t>(60.0 / m_bpm * m_sampleRate + 0.5);
    std::cout << "constructor::bpm: " << m_bpm << "\n";
    std::cout << "constructor::interval: " << m_interval << "\n"; 
    next_click = m_interval;
}

void Clock::SetBPM(const double newBpm) { m_bpm = newBpm; }

void Clock::Process(const uint32_t numberOfSamples) {
    m_totalSamples += numberOfSamples;
    //std::cout << "number of samples, total: " << m_totalSamples << "\n";
    while (m_totalSamples >= next_click) {
        std::cout << "Click!\n";
        next_click += m_interval;  // schedule next click
    }
}

// double Clock::GetCurrentBeatPosition() {
//     return m_currentBeat;
// }

// ClockFollower::ClockFollower(std::shared_ptr<Clock> clockSource, const Subdivision subdivision) :
//                              m_clock(clockSource),
//                              m_subdivision(subdivision),
//                              m_beatDivisor(SelectCorrectBeatDivision(subdivision)) {
//     m_lastBeat = m_clock->GetCurrentBeatPosition();
//     std::cout << "divisor: " << m_beatDivisor << "\n";
// }

// bool ClockFollower::IsBeat() {
//     double beat = m_clock->GetCurrentBeatPosition();
//     double interval = 1.0 / m_beatDivisor;
//     //std::cout << "IsBeat::beat: " << beat << "\n";  
//     //std::cout << "IsBeat::interval: " << interval << "\n"; 

//     // handle wrap-around
//     if (beat < m_lastBeat)
//         m_lastBeat -= 1.0;

//     bool triggered = false;
//     while (beat - m_lastBeat >= interval) {
//         m_lastBeat += interval;
//         triggered = true;
//     }

//     // keep follower phase in range [0, 1)
//     if (m_lastBeat >= 1.0)
//         m_lastBeat -= 1.0;

//     return triggered;
// }

// void ClockFollower::SetSubdivision(const Subdivision subdivision){
//     m_beatDivisor = SelectCorrectBeatDivision(subdivision);
// }

// double ClockFollower::SelectCorrectBeatDivision(const Subdivision subdivision) {
//     switch (subdivision) {
//         case Subdivision::QUARTER_NOTE:
//             return 1.0;

//         case Subdivision::EIGHT_NOTE:
//             return 2.0;
//     }
// }
} // namespace