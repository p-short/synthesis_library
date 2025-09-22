#include "sawwave.h"
#include <algorithm>

namespace musiclib {
    namespace Oscillator {
        double Sawwave::Process() {
            double increment = m_frequency / SoundSource::sampleRate;
            m_phase += increment;
            if (m_phase >= 1.0)
                m_phase -= 1.0;
            
            return m_phase * 2.0 - 1.0;
        }

        Sawwave& Sawwave::SetFrequency(double frequency) {
            m_frequency = frequency;
            return *this;
        }

        Sawwave& Sawwave::SetPhase(double phase) {
            phase = std::min(std::max(0.0, phase), 1.0);
            m_phase = phase;
            return *this;
        }

        Sawwave& Sawwave::SetAmplitude(double amplitude) {
            SoundSource::SetAmplitude(amplitude);
            return *this;
        }
    }
}