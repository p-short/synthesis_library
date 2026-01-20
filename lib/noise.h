#ifndef MUSICLANGUAGE_LIB_NOISE_H
#define MUSICLANGUAGE_LIB_NOISE_H

#include "soundsource.h"
#include <array>
#include <cstddef>

namespace Sculpt {
    namespace Oscillator {
        namespace Noise {
            class White : public SoundSource {
            public:
                virtual ~White() = default;
                White();
                double Process() override;

            private:
                std::array<double, 200000> audioBuffer;
                size_t bufferIndex { 0 };
                //std::random_device rd;
            };
        }
    }
}

// pink noise implementation

/*
#include <iostream>
#include <vector>
#include <random>

class PinkNoise {
public:
    PinkNoise(int ncols = 16)
        : ncols(ncols), state(ncols, 0.0), gen(rd()), dist(-1.0, 1.0)
    {
        // initialize with random values
        for (auto& s : state) {
            s = dist(gen);
        }
    }

    // Generate one pink noise sample
    double process() {
        // pick which column changes this time step
        int col = std::min(geometric(0.5), ncols-1);
        //std::cout << "geo: " << col << "\n";
        //if (col >= ncols) col = 0; // clamp to first column
        
        // update that column
        state[col] = dist(gen);

        // sum all columns to produce outputA
        double total = 0.0;
        for (double s : state) {
            //std::cout << "s: " << s << ", ";
            total += s;
        }
        //std::cout << std::endl;

        return total / ncols;
    }

private:
    int ncols;
    std::vector<double> state; // current value for each column

    // RNG
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> dist;

    // geometric distribution (simulate NumPy’s geometric)
    int geometric(double p) {
        std::geometric_distribution<int> geo(p);
        return geo(gen);
    }
};

int main() {
    PinkNoise pink(16);

    for (int i = 0; i < 20; i++) {
        std::cout << "total: " << pink.process() << std::endl;
    }

    return 0;
}
*/

#endif // MUSICLANGUAGE_LIB_NOISE_H