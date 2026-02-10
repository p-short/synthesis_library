#ifndef MUSICLANGUAGE_LIB_SQUARE_H
#define MUSICLANGUAGE_LIB_SQUARE_H

#include "soundsource.h"

namespace Sculpt {
    namespace Oscillator {
        class Square : public SoundSource {
        public:
            virtual ~Square() = default;
            double Process() override;
            virtual Square& SetFrequency(double frequency);
            virtual Square& SetPhase(double phase);
            virtual Square& SetAmplitude(double amplitude) override;
        private:
            double m_frequency { 440.0 };
            double m_phase = { 0.0 };
        };
    }   
}

#endif // MUSICLANGUAGE_LIB_SQUARE_H