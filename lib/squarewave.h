#ifndef MUSICLANGUAGE_LIB_SQUAREWAVE_H
#define MUSICLANGUAGE_LIB_SQUAREWAVE_H

#include "soundsource.h"

namespace Sculpt {
    namespace Oscillator {
        class Squarewave : public SoundSource {
        public:
            virtual ~Squarewave() = default;
            double Process() override;
            virtual Squarewave& SetFrequency(double frequency);
            virtual Squarewave& SetPhase(double phase);
            virtual Squarewave& SetAmplitude(double amplitude) override;
        private:
            double m_frequency { 440.0 };
            double m_phase = { 0.0 };
        };
    }   
}

#endif // MUSICLANGUAGE_LIB_SQUAREWAVE_H