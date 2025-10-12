#include "sampleplayer.h"
#include "AudioFile.h"

namespace Sculpt {
    bool SamplePlayer::LoadWAVFile(const std::filesystem::path& pathToWAVFile) {
        if (!audioFile)
            audioFile = std::make_shared<AudioFile<double>>();

        try {
            audioFile->load(pathToWAVFile);
            numberOfSamples = audioFile->getNumSamplesPerChannel();
            std::cout << "number of samples: " << numberOfSamples << "\n";
            return true;
        } catch (const std::exception& e) {
            std::cout << e.what() << "\n";
            return false;
        }
    }

    void SamplePlayer::Process(double* leftChannel, double* rightChannel) {
        if (!audioFile) {
            if (leftChannel) *leftChannel = 0.0;
            if (rightChannel) *rightChannel = 0.0;
            return; // maybe throw exception
        }

        if (readIndex < numberOfSamples) {
            if (leftChannel) 
                *leftChannel = audioFile->samples[0][readIndex];

            if (rightChannel)
                *rightChannel = audioFile->samples[1][readIndex];

            readIndex++;

            if (loopEnable && readIndex >= numberOfSamples)
                Reset(); // sets readIndex but to zero

        } else {
            if (leftChannel) *leftChannel = 0.0;
            if (rightChannel) *rightChannel = 0.0;
        }
    }

    void SamplePlayer::Play() {
        Reset();
    }

    bool SamplePlayer::IsPlaying() {
        return readIndex > 0  && readIndex < numberOfSamples;
    }

    // TODO: fix, isPlaying should be true
    void SamplePlayer::Reset() {
        /*
        std::cout << "isPlaying: " << (IsPlaying() ? "true" : "false") << "\n";
        std::cout << "resetting readIndex to 0\n";
        std::cout << "isPlaying: " << (IsPlaying() ? "true" : "false") << "\n";
        */
        readIndex = 0;
    }
}