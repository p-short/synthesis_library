#include "noise.h"
#include "XoshiroCpp.hpp"
#include <random>
#include <algorithm>
#include <iostream>

namespace Sculpt {
    namespace Oscillator {
        namespace Noise {
            White::White() {
                std::random_device rd;
                const uint64_t seed = rd();
                XoshiroCpp::Xoshiro256PlusPlus rng(seed);
                std::uniform_real_distribution<double> dist(-1.0, 1.0);

                for (auto &sample : audioBuffer) 
                    sample = dist(rng);
            }

            double White::Process() {
                if (bufferIndex > audioBuffer.size() - 1)
                    bufferIndex = 0;
                    
                double sample = audioBuffer[bufferIndex];
                bufferIndex++;
                return sample;
            }
        }
    }
}