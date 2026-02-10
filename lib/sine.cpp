#include "sine.h"
#include <cmath>
#include <algorithm>

namespace Sculpt {
    namespace Oscillator {
        double Sine::Process() {
            double increment = m_frequency / SoundSource::sampleRate;
            m_phase += increment;
            if (m_phase >= 1.0)
                m_phase -= 1.0;
            
            return std::sin(m_phase * 2.0 * M_PI);
        }

        Sine& Sine::SetFrequency(double frequency) {
            m_frequency = frequency;
            return *this;
        }

        Sine& Sine::SetPhase(double phase) {
            phase = std::min(std::max(0.0, phase), 1.0);
            m_phase = phase;
            return *this;
        }

        Sine& Sine::SetAmplitude(double amplitude) {
            SoundSource::SetAmplitude(amplitude);
            return *this;
        }

        Sine& Sine::SetPan(double pan) {
            SoundSource::SetPan(pan);
            return *this;
        }

        void Sine::Reset() {
            m_phase = 0.0;
        }
    }
}