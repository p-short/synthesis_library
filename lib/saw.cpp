#include "saw.h"
#include <algorithm>

namespace Sculpt {
    namespace Oscillator {
        double Saw::Process() {
            double increment = m_frequency / SoundSource::sampleRate;
            m_phase += increment;
            if (m_phase >= 1.0)
                m_phase -= 1.0;
            
            return m_phase * 2.0 - 1.0;
        }

        Saw& Saw::SetFrequency(double frequency) {
            m_frequency = frequency;
            return *this;
        }

        Saw& Saw::SetPhase(double phase) {
            phase = std::min(std::max(0.0, phase), 1.0);
            m_phase = phase;
            return *this;
        }

        Saw& Saw::SetAmplitude(double amplitude) {
            SoundSource::SetAmplitude(amplitude);
            return *this;
        }
    }
}