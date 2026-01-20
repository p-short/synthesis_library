#include "sculpt.h" /* <-- include sculpt header to use the sculpt library*/
#include <iostream>
#include <array>
#include <memory>
#include <cstdint>

using namespace Sculpt; 

// 16 voice polyphonic synthesizer
class PolySynth {
    struct Voice {
        bool isActive;
        uint32_t midiNote;
        Oscillator::Sawwave saw;
        Envelope::ADR envelope;
        double duration;
    };

    std::array<Voice, 16> voices;

public:
    PolySynth() {
        for (auto& voice : voices) {
            voice.isActive = false;
            voice.midiNote = 0;
            voice.envelope.SetParameters(0.1, 0.5, 0.2, 0.5); 
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

    // void NoteOff(const uint32_t midiNote) {
    //     for (auto& voice : voices) {
    //         if (voice.isActive && voice.midiNote == midiNote)
    //             voice.envelope.NoteOff();
    //     }
    // }

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

// create PolySynth instance
PolySynth polySynth;

// create a clock object to trigger our poly synth
std::unique_ptr<Clock> masterClock = std::make_unique<Clock>(120.0);
ClockFollower trigger(masterClock.get(), Subdivision::QUARTER_NOTE);

const double gain = 0.25;
double sample = 0.0;
std::array<uint32_t, 3> notes = {60, 67, 72}; // C Major triad
uint32_t i = 0;

FX::Delay::Classic delay(250 /* quarter of a second */);

void Play(double* output) {
    // advance master clock so clock follower (trigger) knows when to pulse
    masterClock->Process();

    // advance PolySynth instance to get next sample
    sample = polySynth.Process();

    if (trigger.IsBeat()) {
        // continually iterate through each note in C Major triad on each trigger 
        if (i > 2) 
            i = 0;

        polySynth.NoteOn(notes[i]);

        // if (i > 0)
        //     polySynth.NoteOff(notes[i - 1]);
        // else 
        //     polySynth.NoteOff(notes[2]);

        i++;
    }
    
    // output signal to left and right channels
    double dryIn = sample * gain;
    double wetOut = delay.Process(dryIn);

    output[0] = wetOut;
    output[1] = output[0];
}

int main() {
    // setup delay
    delay.SetMix(0.5);
    delay.SetFeedback(0.85);
    // create single instance on audio engine
    AudioEngine& dac = AudioEngine::GetInstance();
    dac.AssignCallback(Play); // <-- play (detailed above) gets called every sample
    dac.Start();

    char input;
    std::cout << "\nPlaying ... press <enter> to quit.\n";
    std::cin.get( input );

    dac.Stop();
    return 0;
}
