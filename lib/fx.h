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
        }
    }
}
#endif // MUSICLANGUAGE_LIB_FX_H