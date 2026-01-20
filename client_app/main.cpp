#include <iostream>
#include "sculpt.h"
#include <vector>
#include <array>
#include <cstdint>

using namespace Sculpt;

// TODO: investigate envelope attack being cut short on some notes.
class PolySynth {
    struct Voice {
        bool isActive;
        uint32_t midiNote;
        Oscillator::Sawwave saw;
        Envelope::ADSR envelope;
        double duration;
    };

    std::array<Voice, 16> voices;

public:
    PolySynth() {
        for (auto& voice : voices) {
            voice.isActive = false;
            voice.midiNote = 0;
            voice.envelope.SetParameters(1.0, 1.5, 0.6, 2.0); 
            voice.duration = 0.0;
        }
    }

    void NoteOn(const uint32_t midiNote) {
        for (auto& voice : voices) {
            if (!voice.isActive) {
                voice.isActive = true;
                voice.midiNote = midiNote;
                voice.saw.SetFrequency(Utility::MidiNoteToHz(midiNote));
                voice.envelope.NoteOn();
                return;
            }
        }
    }

    void NoteOff(const uint32_t midiNote) {
        for (auto& voice : voices) {
            if (voice.isActive && voice.midiNote == midiNote)
                voice.envelope.NoteOff();
        }
    }

    double Process() {
        double mix = 0.0;
        double env;
        for (auto& voice : voices) {
            if (voice.isActive) {
                env = voice.envelope.Process();
                mix += voice.saw.Process() * env;

                if (env <= 0.0) {
                    std::cout << "env <= 0.0, marking as inactive\n";
                    voice.isActive = false;
                }
            }
        }
        return mix * 0.2;
    }
};

PolySynth polySynth;

Oscillator::Sawwave saw;
Oscillator::Noise::White whiteNoise;
Utility::Interpolate interpolate(0.0, 1.0, 5.0);
Envelope::ADSR envelope(0.1, 0.2, 0.5, 0.2);
SamplePlayer click;
SamplePlayer tambourine;
double ramp = 0.0;
double frequency = 0.0;
std::array<double, 2> WavLeftAndRightOne;
std::array<double, 2> WavLeftAndRightTwo;
std::unique_ptr<Clock> masterClock = std::make_unique<Clock>(120);
ClockFollower clock_one(masterClock.get(), Subdivision::QUARTER_NOTE);
ClockFollower clock_two(masterClock.get(), Subdivision::EIGHT_NOTE);

void mycallback(double deltaTime, const std::vector<uint8_t>& message) {
    uint8_t statusByte = message[0];
    // upper 4 bits, lower 4 bits is Midi channel.
    uint8_t noteState = statusByte & 0xF0; 

    uint8_t dataByteOne = message[1]; // note values
    uint8_t dataByteTwo = message[2]; // note velocity

    if (noteState == 0x90) {
        std::cout << "Note on" << "\n" << "Note value: " << static_cast<uint32_t>(dataByteOne) << "\n" <<
                     "Note velocity: " << static_cast<uint32_t>(dataByteTwo) << "\n";

        // frequency = musiclib::Utility::MidiNoteToHz(static_cast<uint32_t>(dataByteOne));
        // saw.SetFrequency(frequency);
        // envelope.NoteOn();
        polySynth.NoteOn(static_cast<uint32_t>(dataByteOne));
    }
    
    if (noteState == 0x80) {
        std::cout << "Note off.\n";
        //envelope.NoteOff();
        polySynth.NoteOff(static_cast<uint32_t>(dataByteOne));
    }
}

void Play(double* output) {
    //double envOut = envelope.Process();
    //double sample = saw.Process() * envOut;
    masterClock->Process();
    
    if (clock_one.IsBeat()) 
        click.Play();

    if (clock_two.IsBeat()) 
        tambourine.Play();
    

    //double sample = polySynth.Process();
    click.Process(&WavLeftAndRightOne[0], &WavLeftAndRightOne[1]);
    tambourine.Process(&WavLeftAndRightTwo[0], &WavLeftAndRightTwo[1]);
    //std::cout << "sampleplayer output: " << WavLeftAndRight[0] << " " << WavLeftAndRight[1] << "\n";
    //std::cout << "sampleplayer.isPLaying(): " << (samplePlayer.IsPlaying() ? "true" : "false") << "\n";
    double gain = 0.20;
        
    output[0] = (WavLeftAndRightOne[0] + WavLeftAndRightTwo[0]) * gain;
    output[1] = (WavLeftAndRightOne[1] + WavLeftAndRightTwo[1]) * gain;
}

int main() {
    char input;
    std::cout << "\nsearch for midi devices ... press <enter>\n";
    std::cin.get( input );

    bool result = click.LoadWAVFile("./button-click.wav");
    std::cout << "button-click.wav load result: " << (result ? "true" : "false") << "\n";

    result = tambourine.LoadWAVFile("./tambourine-low.wav");
    std::cout << "tambourine load result: " << (result ? "true" : "false") << "\n";

    // musiclib::MidiManager& midi_mgr = musiclib::MidiManager::GetInstance();

    // const uint32_t numberOfMidiDevices = midi_mgr.GetDeviceCount();
    // if (numberOfMidiDevices == 0) {
    //     std::cout << "No Midi devices found\n";
    //     exit(0);
    // }
    // std::cout << "Number of Midi devices: " << numberOfMidiDevices << "\n";

    // for (size_t i = 0; i < numberOfMidiDevices; ++i)
    //     std::cout << "Device name: " << i << ": " << midi_mgr.GetDeviceName(i) << "\n";
    
    // if (!midi_mgr.ConnectDevice(0)) {
    //     std::cout << "Failed to open device 0\n";
    //     exit(0);
    // } 
    // std::cout << "Connected to device 0\n";

    // midi_mgr.AssignCallback(mycallback);
    // std::cout << "Midi callback assigned\n";
    
    AudioEngine& dac = AudioEngine::GetInstance();
    dac.AssignCallback(Play);
    dac.Start();

    std::cout << "\nPlaying ... press <enter> to quit.\n";
    std::cin.get( input );

    dac.Stop();
    return 0;
}

// int audioCallback(void *outputBuffer, void *,
//     unsigned int nBufferFrames,
//     double /*streamTime*/,
//     RtAudioStreamStatus status,
//     void *userData)
// {
//     if (status) std::cerr << "Stream underflow/overflow detected!" << std::endl;
//     // auto *osc = static_cast<musiclib::Oscillator::Sinewave*>(userData);
//     auto *sources = static_cast<std::vector<std::unique_ptr<musiclib::SoundSource>>*>(userData);
//     float *buffer = static_cast<float*>(outputBuffer);

//     // double pan = 0.5; // center
//     // double leftGain  = std::cos(pan * M_PI_2);
//     // double rightGain = std::sin(pan * M_PI_2);

//     // for (unsigned int i = 0; i < nBufferFrames; i++) {
//     //     double sample = osc->Process() * 0.2;
//     //     buffer[2*i]     = static_cast<float>(sample);
//     //     buffer[2*i + 1] = static_cast<float>(sample);
//     // }

//     for (unsigned int i = 0; i < nBufferFrames; i++) {
//       double left = 0.0;
//       double right = 0.0;

//       for (auto &src : *sources) {
//           double sample = src->Process();

//           double leftGain  = std::cos(src->GetPan() * M_PI_2);
//           double rightGain = std::sin(src->GetPan() * M_PI_2);

//           left  += (sample * leftGain) * 0.20;
//           right += (sample * rightGain) * 0.20;
//       }

//       buffer[2*i]     = static_cast<float>(left);
//       buffer[2*i + 1] = static_cast<float>(right);
//   }
//     return 0;
// }

// int main() {
//     RtAudio dac;
//     std::vector<unsigned int> deviceIds = dac.getDeviceIds();
//     if ( deviceIds.size() < 1 ) {
//       std::cout << "\nNo audio devices found!\n";
//       exit( 0 );
//     }

//     musiclib::SoundSource::sampleRate = 44100.0;
   
//     RtAudio::StreamParameters parameters;
//     parameters.deviceId = dac.getDefaultOutputDevice();
//     parameters.nChannels = 2;
//     parameters.firstChannel = 0;
//     unsigned int sampleRate = 44100;
//     unsigned int bufferFrames = 256; // 256 sample frames
//     double data[2] = {0, 0};

//     // Create oscillator and pass it to the callback
//     //musiclib::Oscillator::Sinewave sinewave;
//     //sinewave.SetFrequency(880.0).SetAmplitude(1).SetPan(0.5);

//     //musiclib::Oscillator::Noise::White whiteNoise;

//     std::vector<std::unique_ptr<musiclib::SoundSource>> sources;

//     std::unique_ptr<musiclib::Oscillator::Sinewave> sinewave = nullptr;
//     sinewave = std::make_unique<musiclib::Oscillator::Sinewave>();
//     sinewave->SetFrequency(880.0).SetPan(0.0);
//     sources.push_back(std::move(sinewave));
//     sources.push_back(std::make_unique<musiclib::Oscillator::Noise::White>());

//     sources[0]->SetAmplitude(1).SetPan(0.0);
//     sources[1]->SetAmplitude(1).SetPan(1.0);
   
//     if ( dac.openStream( &parameters, NULL, RTAUDIO_FLOAT32, sampleRate,
//                          &bufferFrames, &audioCallback, &sources ) ) {
//       std::cout << '\n' << dac.getErrorText() << '\n' << std::endl;
//       exit( 0 ); // problem with device settings
//     }
   
//     // Stream is open ... now start it.
//     if ( dac.startStream() ) {
//       std::cout << dac.getErrorText() << std::endl;
//       goto cleanup;
//     }
    
//     char input;
//     std::cout << "\nPlaying ... press <enter> to quit.\n";
//     std::cin.get( input );
   
//     // Block released ... stop the stream
//     if ( dac.isStreamRunning() )
//       dac.stopStream();  // or could call dac.abortStream();
   
//    cleanup:
//     if ( dac.isStreamOpen() ) dac.closeStream();
   
//     return 0;
// }