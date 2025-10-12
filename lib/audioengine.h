#ifndef MUSICLANGUAGE_LIB_AUDIOENGINE_H
#define MUSICLANGUAGE_LIB_AUDIOENGINE_H

#include <functional>
#include <memory>

class RtAudio;

namespace Sculpt {
    class AudioEngine {
    public:
        ~AudioEngine();
        static AudioEngine& GetInstance();
        void AssignCallback(std::function<void (double *)> callback);
        void Start();
        void Stop();

        bool isPlaying { false };

    private:
        static int Callback(void *outputBuffer, void *,
                            unsigned int nBufferFrames, double,
                            uint32_t status, void *userData);
        std::unique_ptr<RtAudio> m_dac { nullptr };
        std::function<void (double* )> m_callback;
        uint32_t m_sampleRate { 44100 };
        uint32_t m_bufferFrames = { 256 }; 
        double m_data[2] = {0, 0};
    };
}

#endif // MUSICLANGUAGE_LIB_AUDIOENGINE_H