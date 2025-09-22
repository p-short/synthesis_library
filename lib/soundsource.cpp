#include "soundsource.h"

namespace musiclib {
    double SoundSource::sampleRate = 44100.0;

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
