#ifndef MUSICLANGUAGE_LIB_SAWWAVE_H
#define MUSICLANGUAGE_LIB_SAWWAVE_H

#include "soundsource.h"

namespace musiclib {
    namespace Oscillator {
        class Sawwave : public SoundSource {
        public:
            virtual ~Sawwave() = default;
            double Process() override;
            virtual Sawwave& SetFrequency(double frequency);
            virtual Sawwave& SetPhase(double phase);
            virtual Sawwave& SetAmplitude(double amplitude) override;
        private:
            double m_frequency { 440.0 };
            double m_phase = { 0.0 };
        };
    }   
}

#endif // MUSICLANGUAGE_LIB_SAWWAVE_H