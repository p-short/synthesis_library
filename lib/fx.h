#ifndef MUSICLANGUAGE_LIB_FX_H
#define MUSICLANGUAGE_LIB_FX_H

#include <memory>

namespace Sculpt {
    namespace FX {
        namespace Delay{
            class Classic {
            public:
                Classic(double timeInMilliseconds);
                void SetTime(double timeInMilliseconds);
                void SetMix(double mix);
                void SetFeedback(double feedback);
                double Process(double inputSample);
            
            private:
                std::unique_ptr<double[]> m_buffer { nullptr };
                double m_feedback { 0.5 };
                double m_mix { 0.5 };
                double m_numberOfSamples { 0.0 };
                uint32_t m_writeIndex { 0 };
            };

            class Tape {
            public:
                Tape(double TimeInMilliseconds);
                void SetTime(double timeInMilliseconds);
                void SetMix(double mix);
                void SetFeedback(double feedback);
                double Process(double inputSample);

            private:
                std::unique_ptr<double[]> m_buffer { nullptr };
                double m_feedback { 0.5 };
                double m_mix { 0.5 };
                uint32_t m_writeIndex { 0 };
                double m_baseDelaySamples = 0;
                uint32_t m_bufferSize = 0;

                // Feedback & mix
                //double m_feedback = 0.5;
                //double m_mix = 0.5;
            
                // Modulation
                double m_wowAmount = 0.0;     // in samples
                double m_flutterAmount = 0.0; // in samples
            
                double m_wowPhase = 0.0;
                double m_flutterPhase = 0.0;
            
                // Speeds (tweakable)
                const double m_wowRate = 0.3;     // Hz (slow)
                const double m_flutterRate = 7.0; // Hz (fast)

                const double m_sampleRate = 44100.0; 
            
                double GetModulatedDelay();
                double ReadFractional(double readPos);
            };
        }
    }
}
#endif // MUSICLANGUAGE_LIB_FX_H