#include "sinewave.h"
#include <cmath>
#include <algorithm>

namespace Sculpt {
    namespace Oscillator {
        double Sinewave::Process() {
            double increment = m_frequency / SoundSource::sampleRate;
            m_phase += increment;
            if (m_phase >= 1.0)
                m_phase -= 1.0;
            
            return std::sin(m_phase * 2.0 * M_PI);
        }

        Sinewave& Sinewave::SetFrequency(double frequency) {
            m_frequency = frequency;
            return *this;
        }

        Sinewave& Sinewave::SetPhase(double phase) {
            phase = std::min(std::max(0.0, phase), 1.0);
            m_phase = phase;
            return *this;
        }

        Sinewave& Sinewave::SetAmplitude(double amplitude) {
            SoundSource::SetAmplitude(amplitude);
            return *this;
        }

        Sinewave& Sinewave::SetPan(double pan) {
            SoundSource::SetPan(pan);
            return *this;
        }
    }
}