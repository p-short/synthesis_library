#include "envelope.h"
#include <iostream>

namespace musiclib {
    Envelope::Envelope() : Envelope(0.1, 0.2, 0.5, 0.5) {}
    
    Envelope::Envelope(double attack, double decay, double sustain, double release) : 
                       m_attackRamp(0.0, 1.0, attack), m_decayRamp(1.0, sustain, decay),
                       m_releaseRamp(sustain, 0.0, release), m_attack(attack),
                       m_decay(decay), m_sustainLevel(sustain), m_release(release) {}

    void Envelope::SetParameters(double attack, double decay, double sustain, double release) {
        m_attackRamp.SetParameters(0.0, 1.0, attack);
        m_decayRamp.SetParameters(1.0, sustain, decay);
        m_releaseRamp.SetParameters(sustain, 0.0, release);
        m_attack = attack;
        m_decay = decay;
        m_sustainLevel = sustain;
        m_release = release;
    }

    void Envelope::NoteOn() {
        m_attackRamp.SetParameters(0.0, 1.0, m_attack);
        stage = Stage::ATTACK;
    }

    void Envelope::NoteOff() {
        if (stage != Stage::NOT_ACTIVE) {
            m_releaseRamp.SetParameters(currentEnvelopeValue, 0.0, m_release);
            stage = Stage::RELEASE;
        }
    }

    double Envelope::Process() {
        switch (stage) {
            case Stage::NOT_ACTIVE: 
                return 0.0;
            
            case Stage::ATTACK: {
                currentEnvelopeValue = m_attackRamp.Process();

                if (currentEnvelopeValue >= 1.0) {
                    currentEnvelopeValue = 1.0;
                    m_attackRamp.SetParameters(0.0, 1.0, m_attack);
                    AdvanceStage();
                }

                break;
            }

            case Stage::DECAY: {
                currentEnvelopeValue = m_decayRamp.Process();

                if (currentEnvelopeValue <= m_sustainLevel) {
                    currentEnvelopeValue = m_sustainLevel;
                    m_decayRamp.SetParameters(1.0, m_sustainLevel, m_decay);
                    AdvanceStage();
                }

                break;
            }

            case Stage::SUSTAIN:
                currentEnvelopeValue = m_sustainLevel; 
                break;

            case Stage::RELEASE: {
                currentEnvelopeValue = m_releaseRamp.Process();

                if (currentEnvelopeValue <= 0.0) {
                    currentEnvelopeValue = 0.0;
                    AdvanceStage();
                }

                break;
            }
        }
        return currentEnvelopeValue;
    }

    void Envelope::AdvanceStage() {
        if (stage == Stage::ATTACK) {
            stage = Stage::DECAY; 
            return;
        }

        if (stage == Stage::DECAY) {
            stage = Stage::SUSTAIN;
            return;
        }

        if (stage == Stage::RELEASE) {
            currentEnvelopeValue = 0.0;
            stage = Stage::NOT_ACTIVE;
        }
    }
}