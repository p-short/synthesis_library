#ifndef MUSICLANGUAGE_LIB_SOUNDSOURCE_H
#define MUSICLANGUAGE_LIB_SOUNDSOURCE_H

namespace musiclib {
    class SoundSource {
    public:
        virtual ~SoundSource() = default;
        virtual double Process();
        virtual void Process(double* leftChannel, double* rightChannel);
        virtual SoundSource& SetAmplitude(double amplitude);
        virtual SoundSource& SetPan(double pan);
        virtual double GetAmplitude();
        virtual double GetPan();

        static double sampleRate;
    private:
        double m_amplitude { 1.0 };
        double m_pan { 0.5 };
    };
}

#endif // MUSICLANGUAGE_LIB_SOUNDSOURCE_H