#ifndef MUSICLANGUAGE_LIB_SAW_H
#define MUSICLANGUAGE_LIB_SAW_H

#include "soundsource.h"

namespace Sculpt {
    namespace Oscillator {
        class Saw : public SoundSource {
        public:
            virtual ~Saw() = default;
            double Process() override;
            virtual Saw& SetFrequency(double frequency);
            virtual Saw& SetPhase(double phase);
            virtual Saw& SetAmplitude(double amplitude) override;
        private:
            double m_frequency { 440.0 };
            double m_phase = { 0.0 };
        };
    }   
}

#endif // MUSICLANGUAGE_LIB_SAW_H