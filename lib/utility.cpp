#include "utility.h"
#include "midinotetoHz.h"
#include <iostream>

namespace Sculpt {
    namespace Utility {
        Interpolate::Interpolate(double startValue, double endValue, double durationInSeconds) {
            m_current = startValue;
            m_endValue = endValue;
            m_increment = (endValue - startValue) / (44100.0 * durationInSeconds);
        }

        void Interpolate::SetParameters(double startValue, double endValue, double durationInSeconds) {
            m_current = startValue;
            m_endValue = endValue;
            m_increment = (endValue - startValue) / (44100.0 * durationInSeconds);
        }

        double Interpolate::Process() {
            if ((m_increment > 0 && m_current < m_endValue) ||
                (m_increment < 0 && m_current > m_endValue)) {
                m_current += m_increment;
            }   

            return m_current;
        }

        double MidiNoteToHz(uint32_t midiNote) {
            return MidiNoteToHzContainer[midiNote];
        }

        double MillisecondsToSamples(double numberOfMilliseconds) {
            return (numberOfMilliseconds * 44100.0) / 1000.0;
        }

        double SamplesToMilliseconds(double numberOfSamples) {
            return (numberOfSamples / 44100.0) * 1000.0;
        }
    }
}