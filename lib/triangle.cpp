#include "triangle.h"
#include <cmath>
#include <algorithm>

namespace Sculpt {
    namespace Oscillator {
        double Triangle::Process() {
            double increment = m_frequency / SoundSource::sampleRate;
            m_phase += increment;
            if (m_phase >= 1.0)
                m_phase -= 1.0;
            
            return 2.0 * std::abs(2.0 * m_phase - 1.0) - 1.0;
        }

        Triangle& Triangle::SetFrequency(double frequency) {
            m_frequency = frequency;
            return *this;
        }

        Triangle& Triangle::SetPhase(double phase) {
            phase = std::min(std::max(0.0, phase), 1.0);
            m_phase = phase;
            return *this;
        }

        Triangle& Triangle::SetAmplitude(double amplitude) {
            SoundSource::SetAmplitude(amplitude);
            return *this;
        }
    }
}