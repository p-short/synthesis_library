#ifndef MUSICLANGUAGE_LIB_UTILITIES_H
#define MUSICLANGUAGE_LIB_UTILITIES_H

#include <cstdint>

namespace Sculpt {
    namespace Utility {
        class Interpolate {
        public:
            Interpolate(double startValue, double endValue, double durationInSeconds);
            void SetParameters(double startValue, double endValue, double durationInSeconds);
            double Process();

        private:
            double m_current {};
            double m_endValue {};
            double m_increment {};
        };

        double MidiNoteToHz(uint32_t midiNote);

        // TODO: add SamplesToMilliseconds
        // TODO: add MillisecondsToSamples
        
    }
}
#endif // MUSICLANGUAGE_LIB_UTILITIES_H