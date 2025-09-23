#include <iostream>
#include "musiclanguage.h"
#include <vector>
#include <cstdint>

//musiclib::Oscillator::Sinewave sinewave;
//musiclib::Oscillator::Trianglewave tri;
//musiclib::Oscillator::Squarewave rect;
musiclib::Oscillator::Sawwave saw;
musiclib::Oscillator::Noise::White whiteNoise;
musiclib::Utility::Interpolate interpolate(0.0, 1.0, 5.0);
musiclib::Envelope envelope(5.0, 2.0, 0.5, 5.0);
double ramp = 0.0;

void mycallback(double deltaTime, const std::vector<uint8_t>& message) {
    uint8_t statusByte = message[0];
    uint8_t noteState = statusByte & 0xF0; // upper 4 bits, lower 4 bits is Midi channel.

    uint8_t dataByteOne = message[1]; // note values
    uint8_t dataByteTwo = message[2]; // note velocity

    if (noteState == 0x90) {
        std::cout << "Note on.\n";
        std::cout << "Note value: " << static_cast<int32_t>(dataByteOne) << "\n" <<
        "Note velocity: " << static_cast<int32_t>(dataByteTwo) << "\n";
        envelope.NoteOn();
    }
    
    if (noteState == 0x80) {
        std::cout << "Note off.\n";
        envelope.NoteOff();
    }
}

void Play(double* output) {
    double envOut = envelope.Process();
    std::cout << "envelope.Process: " << envOut << "\n";

    //ramp = interpolate.Process();
    double sample = saw.Process() * envOut; //+ (whiteNoise.Process() * 0.5);
    //double mix = sample * ramp;
    output[0] = sample * 0.20;
    output[1] = output[0];
}

int main() {

    char input;
    std::cout << "\nsearch for midi devices ... press <enter>\n";
    std::cin.get( input );

    musiclib::MidiManager& midi_mgr = musiclib::MidiManager::GetInstance();

    const uint32_t numberOfMidiDevices = midi_mgr.GetDeviceCount();
    if (numberOfMidiDevices == 0) {
        std::cout << "No Midi devices found\n";
        exit(0);
    }
    std::cout << "Number of Midi devices: " << numberOfMidiDevices << "\n";

    for (size_t i = 0; i < numberOfMidiDevices; ++i)
        std::cout << "Device name: " << i << ": " << midi_mgr.GetDeviceName(i) << "\n";
    
    if (!midi_mgr.ConnectDevice(0)) {
        std::cout << "Failed to open device 0\n";
        exit(0);
    } 
    std::cout << "Connected to device 0\n";

    midi_mgr.AssignCallback(mycallback);
    std::cout << "Midi callback assigned\n";
    
    musiclib::AudioEngine& dac = musiclib::AudioEngine::GetInstance();
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