#include "fx.h"
#include "utility.h"
#include <algorithm>

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
        }
    }
}