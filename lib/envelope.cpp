#include "envelope.h"
#include <iostream>

namespace musiclib {
    Envelope::Envelope(double attack, double decay, double sustain, double release) : 
                       m_attackRamp(0.0, 1.0, attack),
                       m_decayRamp(1.0, sustain, decay),
                       m_releaseRamp(sustain, 0.0, release),
                       m_attack(attack),
                       m_decay(decay),
                       m_sustainLevel(sustain),
                       m_release(release) {}

    void Envelope::NoteOn() {
        m_attackRamp.SetParameters(0.0, 1.0, m_attack);
        stage = Stage::ATTACK;

        // if (m_attackInc > 0.0) {
        //     stage = Stage::ATTACK;
        //     std::cout << "NoteOn: Attack\n";
        // } else if (m_decayInc >= 0.0) {
        //     currentEnvelopeValue = 1.0;
        //     stage = Stage::DECAY;
        //     std::cout << "NoteOn: Decay\n";
        // } else {
        //     currentEnvelopeValue = m_sustainLevel;
        //     stage = Stage::SUSTAIN;
        //     std::cout << "NoteOn: Sustain\n";
        // }
    }

    void Envelope::NoteOff() {
        if (stage != Stage::NOT_ACTIVE) {
            if (m_sustainLevel > 0.0) {
                stage = Stage::RELEASE;
            } else {
                currentEnvelopeValue = 0.0;
                stage = Stage::NOT_ACTIVE;
            } 
        }
    }

    //int count = 0;
    double Envelope::Process() {
        // count++;
        // if (count > 1000) 
        //     count = 0;

        switch (stage) {
            case Stage::NOT_ACTIVE: {
                //if (count == 0)
                    //std::cout << "Process::NOT_ACTIVE\n";
                return 0.0;
            }

            case Stage::ATTACK: {
                //if (count == 0)
                    //std::cout << "Process::ATTACK\n";

                currentEnvelopeValue = m_attackRamp.Process();

                if (currentEnvelopeValue >= 1.0) {
                    currentEnvelopeValue = 1.0;
                    m_attackRamp.SetParameters(0.0, 1.0, m_attack);
                    //std::cout << "Processing:: reseting\n";
                    AdvanceStage();
                }

                //std::cout << "breaking\n";
                break;
            }

            case Stage::DECAY: {
                //if (count == 0)
                    //std::cout << "Process::DECAY\n";
                currentEnvelopeValue = m_decayRamp.Process();

                if (currentEnvelopeValue <= m_sustainLevel) {
                    currentEnvelopeValue = m_sustainLevel;
                    m_decayRamp.SetParameters(1.0, m_sustainLevel, m_decay);
                    AdvanceStage();
                }

                break;
            }

            case Stage::SUSTAIN:
                //if (count == 0)
                    //std::cout << "Process::SUSTAIN\n";

                currentEnvelopeValue = m_sustainLevel; 
                break;

            case Stage::RELEASE: {
                //if (count == 0)
                    //std::cout << "Process::RELEASE\n";

                currentEnvelopeValue = m_releaseRamp.Process();

                if (currentEnvelopeValue <= 0.0) {
                    currentEnvelopeValue = 0.0;
                    m_releaseRamp.SetParameters(m_sustainLevel, 0.0, m_release);
                    AdvanceStage();
                }

                break;
            }
        }

        return currentEnvelopeValue;
    }

    void Envelope::AdvanceStage() {
        if (stage == Stage::ATTACK) {
            stage = Stage::DECAY; //m_decayInc > 0.0f ? Stage::DECAY : Stage::SUSTAIN;
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