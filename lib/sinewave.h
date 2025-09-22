
#ifndef MUSICLANGUAGE_LIB_SINEWAVE_H
#define MUSICLANGUAGE_LIB_SINEWAVE_H

#include "soundsource.h"

namespace musiclib {
    namespace Oscillator {
        class Sinewave : public SoundSource {
        public:
            virtual ~Sinewave() = default;
            double Process() override;
            virtual Sinewave& SetFrequency(double frequency);
            virtual Sinewave& SetPhase(double phase);
            virtual Sinewave& SetAmplitude(double amplitude) override;
            virtual Sinewave& SetPan(double pan) override;
        private:
            double m_frequency { 440.0 };
            double m_phase = { 0.0 };
        };
    }   
}

#endif // MUSICLANGUAGE_LIB_SINEWAVE_H