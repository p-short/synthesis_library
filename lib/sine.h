
#ifndef MUSICLANGUAGE_LIB_SINE_H
#define MUSICLANGUAGE_LIB_SINE_H

#include "soundsource.h"

namespace Sculpt {
    namespace Oscillator {
        class Sine : public SoundSource {
        public:
            virtual ~Sine() = default;
            double Process() override;
            virtual Sine& SetFrequency(double frequency);
            virtual Sine& SetPhase(double phase);
            virtual Sine& SetAmplitude(double amplitude) override;
            virtual Sine& SetPan(double pan) override;
            void Reset(); // TODO: add to rest of oscillator classes
        private:
            double m_frequency { 440.0 };
            double m_phase = { 0.0 };
        };
    }   
}

#endif // MUSICLANGUAGE_LIB_SINE_H