#include "square.h"
#include <algorithm>

namespace Sculpt {
    namespace Oscillator {
        double Square::Process() {
            double increment = m_frequency / SoundSource::sampleRate;
            m_phase += increment;
            if (m_phase >= 1.0)
                m_phase -= 1.0;
            
            return (m_phase < 0.5) ? 1.0 : -1.0;
        }

        Square& Square::SetFrequency(double frequency) {
            m_frequency = frequency;
            return *this;
        }

        Square& Square::SetPhase(double phase) {
            phase = std::min(std::max(0.0, phase), 1.0);
            m_phase = phase;
            return *this;
        }

        Square& Square::SetAmplitude(double amplitude) {
            SoundSource::SetAmplitude(amplitude);
            return *this;
        }
    }
}