#include "squarewave.h"
#include <algorithm>

namespace musiclib {
    namespace Oscillator {
        double Squarewave::Process() {
            double increment = m_frequency / SoundSource::sampleRate;
            m_phase += increment;
            if (m_phase >= 1.0)
                m_phase -= 1.0;
            
            return (m_phase < 0.5) ? 1.0 : -1.0;
        }

        Squarewave& Squarewave::SetFrequency(double frequency) {
            m_frequency = frequency;
            return *this;
        }

        Squarewave& Squarewave::SetPhase(double phase) {
            phase = std::min(std::max(0.0, phase), 1.0);
            m_phase = phase;
            return *this;
        }

        Squarewave& Squarewave::SetAmplitude(double amplitude) {
            SoundSource::SetAmplitude(amplitude);
            return *this;
        }
    }
}