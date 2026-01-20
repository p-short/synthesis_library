#include "fx.h"
#include "utility.h"
#include <algorithm>
#include <cmath>

namespace Sculpt {
    namespace FX {
        namespace Delay {
            Classic::Classic(double timeInMilliseconds) {
                SetTime(timeInMilliseconds);
            }

            void Classic::SetTime(double timeInMilliseconds) {
                m_numberOfSamples = Utility::MillisecondsToSamples(timeInMilliseconds);
                m_buffer = std::make_unique<double[]>(m_numberOfSamples);
                std::fill(m_buffer.get(), m_buffer.get() + static_cast<size_t>(m_numberOfSamples), 0);
            }

            void Classic::SetMix(double mix) { m_mix = mix; }

            void Classic::SetFeedback(double feedback) { m_feedback = feedback; }

            double Classic::Process(double inputSample) {
                const uint32_t bufferSize   = static_cast<uint32_t>(m_numberOfSamples);
                const uint32_t delaySamples = bufferSize;
            
                // compute properly delayed read index
                const uint32_t readIndex =
                    (m_writeIndex + bufferSize - delaySamples) % bufferSize;
            
                const double delayedSample = m_buffer[readIndex];
            
                // write feedback contents
                m_buffer[m_writeIndex] = inputSample + delayedSample * m_feedback;
            
                // advance write position
                m_writeIndex = (m_writeIndex + 1) % bufferSize;
            
                // wet/dry mix
                return inputSample * (1.0 - m_mix) + delayedSample * m_mix;
            }

            Tape::Tape(double timeInMilliseconds) {
                SetTime(timeInMilliseconds);
            }

            void Tape::SetTime(double timeInMiliseconds) {
                // 3 seconds for plenty of head room
                // as modulation cause drift
                size_t bufferSize = m_sampleRate * 3; 
                m_buffer = std::make_unique<double[]>(bufferSize);
                std::fill(m_buffer.get(), m_buffer.get() + bufferSize, 0);

                m_baseDelaySamples = Utility::MillisecondsToSamples(timeInMiliseconds);
            }

            void Tape::SetMix(double mix) { m_mix = mix; }

            void Tape::SetFeedback(double feedback) { m_feedback = feedback; }

            double Process(double inputSignal) {
                return 0.0;
            }

            double Tape::GetModulatedDelay() {
                // advance LFO phases
                m_wowPhase += (2.0 * M_PI * m_wowRate) / m_sampleRate;
                m_flutterPhase += (2.0 * M_PI * m_flutterRate) / m_sampleRate;

                if (m_wowPhase >= 2.0 * M_PI) m_wowPhase -= 2.0 * M_PI;
                if (m_flutterPhase >= 2.0 * M_PI) m_flutterPhase -= 2.0 * M_PI;

                double wow = std::sin(m_wowPhase) * m_wowAmount;
                double flutter = std::sin(m_flutterPhase) * m_flutterAmount;

                return m_baseDelaySamples + wow + flutter;
            }
            
            double Tape::ReadFractional(double readPos){ return 0.0; }
        }
    }
}