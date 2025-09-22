#ifndef MUSICLANGUAGE_LIB_ENVELOPE_H
#define MUSICLANGUAGE_LIB_ENVELOPE_H

#include "utility.h"

namespace musiclib {
    class Envelope {
    public:
        Envelope(double attack, double decay, double sustain, double release);
        void NoteOn();
        void NoteOff();
        double Process();
        
    private:
        Utility::Interpolate m_attackRamp;
        Utility::Interpolate m_decayRamp;
        Utility::Interpolate m_releaseRamp;

        double m_attack;
        double m_decay;
        double m_sustainLevel;
        double m_release;
        
        double m_attackInc { 0.0 };
        double m_decayInc { 0.0 };

        enum class Stage { NOT_ACTIVE = 0,
                           ATTACK,
                           DECAY,
                           SUSTAIN,
                           RELEASE
        };

        Stage stage { Stage::NOT_ACTIVE };
        double currentEnvelopeValue { 0.0 };

        void AdvanceStage();
    };
}

#endif // MUSICLANGUAGE_LIB_ENVELOPE_H