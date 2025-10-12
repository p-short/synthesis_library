#include "soundsource.h"

namespace Sculpt {
    double SoundSource::sampleRate = 44100.0;

    double SoundSource::Process() {
        return 0.0;
    }

    void SoundSource::Process(double* leftChannel, double* rightChannel) {}

    SoundSource& SoundSource::SetAmplitude(double amplitude) {
        m_amplitude = amplitude;
        return *this;
    }
    SoundSource& SoundSource::SetPan(double pan) {
        m_pan = pan;
        return *this;
    }

    double SoundSource::GetAmplitude() {
        return m_amplitude;
    }

    double SoundSource::GetPan() {
        return m_pan;
    }
}
