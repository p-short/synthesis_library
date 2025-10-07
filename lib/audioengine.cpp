#include "audioengine.h"
#include "RtAudio.h"

namespace musiclib {

    AudioEngine::~AudioEngine() {
        if (m_dac && m_dac->isStreamOpen()) 
            m_dac->closeStream();
    }

    AudioEngine& AudioEngine::GetInstance() {
        static AudioEngine instance;
        return instance;
    }

    void AudioEngine::AssignCallback(std::function<void (double *)> callback) {
        m_callback = std::move(callback);
    }

    void AudioEngine::Start() {
        if (!m_dac)
            m_dac = std::make_unique<RtAudio>();

        if (m_dac->isStreamRunning())
            return;

        RtAudio::StreamParameters parameters;
        parameters.deviceId = m_dac->getDefaultOutputDevice();
        parameters.nChannels = 2;
        parameters.firstChannel = 0;

        m_dac->openStream(&parameters, NULL, RTAUDIO_FLOAT64, m_sampleRate,
                        &m_bufferFrames, &AudioEngine::Callback, this);

        m_dac->startStream();
    }

    void AudioEngine::Stop() {
        if (m_dac && m_dac->isStreamRunning())
            m_dac->stopStream();
    }

    int AudioEngine::Callback(void *outputBuffer, void *,
                              unsigned int nBufferFrames, double,
                              uint32_t status, void *userData) {
        double *buffer = static_cast<double *>(outputBuffer);
        auto *engine = static_cast<AudioEngine *>(userData);

        if (status)
        std::cout << "Stream underflow detected!" << std::endl;

        //std::cout << "nBufferFrames: " << nBufferFrames << "\n";

        for (unsigned int i = 0; i < nBufferFrames; ++i) {
            if (engine->m_callback) 
                engine->m_callback(engine->m_data);
            
        // } else {
        //    engine->m_data[0] = 0.0;
        //     engine->m_data[1] = 0.0;
        // }

            buffer[2 * i]     = static_cast<double>(engine->m_data[0]);
            buffer[2 * i + 1] = static_cast<double>(engine->m_data[1]);
        }
        
         return 0;
    }
}