#ifndef MUSICLANGUAGE_LIB_TRIANGLEWAVE_H
#define MUSICLANGUAGE_LIB_TRIANGLEWAVE_H

#include "soundsource.h"

namespace musiclib {
    namespace Oscillator {
        class Trianglewave : public SoundSource {
        public:
            virtual ~Trianglewave() = default;
            double Process() override;
            virtual Trianglewave& SetFrequency(double frequency);
            virtual Trianglewave& SetPhase(double phase);
            virtual Trianglewave& SetAmplitude(double amplitude) override;
        private:
            double m_frequency { 440.0 };
            double m_phase = { 0.0 };
        };
    }   
}

#endif // MUSICLANGUAGE_LIB_TRIANGLEWAVE_H