#ifndef MUSICLANGUAGE_LIB_SAMPLEPLAYER_H
#define MUSICLANGUAGE_LIB_SAMPLEPLAYER_H

#include "soundsource.h"
#include <filesystem>

template <class T>
class AudioFile;

// TODO: TIDY this up!
namespace Sculpt {
    class SamplePlayer : public SoundSource {
    public:
        bool LoadWAVFile(const std::filesystem::path& pathToWAVFile);
        uint32_t GetBufferSize();
        uint32_t GetSamplerate();
        uint32_t GetNumberOfChannels();
        void SetPlaybackSpeed(const double playbackSpeed);
        void SetStartPoint(const uint32_t start);
        void SetEndPoint(const uint32_t end);
        // TODO: Process to default to play once, to play again will need resetting.
        // to loop sample you'll need to set loopEnable to true.
        void Process(double* leftChannel, double* rightChannel) override;
        void Play();
        bool IsPlaying();
        uint32_t GetCurrentPosition();
        void Reset();
        // double GetSample(const uint32_t index);
        bool loopEnable { false };
    private:
        std::shared_ptr<AudioFile<double>> audioFile { nullptr };
        uint32_t readIndex { 0 };
        uint32_t numberOfSamples { 0 };
    };
}

#endif // MUSICLANGUAGE_LIB_SAMPLEPLAYER_H