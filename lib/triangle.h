#ifndef MUSICLANGUAGE_LIB_TRIANGLE_H
#define MUSICLANGUAGE_LIB_TRIANGLE_H

#include "soundsource.h"

namespace Sculpt {
    namespace Oscillator {
        class Triangle : public SoundSource {
        public:
            virtual ~Triangle() = default;
            double Process() override;
            virtual Triangle& SetFrequency(double frequency);
            virtual Triangle& SetPhase(double phase);
            virtual Triangle& SetAmplitude(double amplitude) override;
        private:
            double m_frequency { 440.0 };
            double m_phase = { 0.0 };
        };
    }   
}

#endif // MUSICLANGUAGE_LIB_TRIANGLE_H