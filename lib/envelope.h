#ifndef MUSICLANGUAGE_LIB_ENVELOPE_H
#define MUSICLANGUAGE_LIB_ENVELOPE_H

#include "utility.h"

namespace Sculpt {
    namespace Envelope {
        class ADSR {
        public:
            ADSR();
            ADSR(double attack, double decay, double sustain, double release);
            void SetParameters(double attack, double decay, double sustain, double release);
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

            enum class Stage { NOT_ACTIVE = 0, ATTACK, DECAY, SUSTAIN, RELEASE };
            Stage stage { Stage::NOT_ACTIVE };
            double currentEnvelopeValue { 0.0 };
            void AdvanceStage();
        };

        class ADR {
        public:
            ADR();
            ADR(double attack, double decayLevel, double decay, double release);
            void SetParameters(double attack, double decayLevel, double decay, double release);
            void NoteOn();
            double Process();
            void Reset();
            
        private:
            Utility::Interpolate m_attackRamp;
            Utility::Interpolate m_decayRamp;
            Utility::Interpolate m_releaseRamp;

            double m_attack;
            double m_decayLevel;
            double m_decay;
            double m_release;

            enum class Stage { NOT_ACTIVE = 0, ATTACK, DECAY, RELEASE };
            Stage stage { Stage::NOT_ACTIVE };
            double currentEnvelopeValue { 0.0 };
            void AdvanceStage();
        };
    }
}

#endif // MUSICLANGUAGE_LIB_ENVELOPE_H