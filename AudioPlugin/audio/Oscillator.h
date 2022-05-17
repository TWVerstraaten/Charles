//
// Created by pc on 16-5-22.
//

#ifndef AUDIO_PLUGIN_EXAMPLE_OSCILLATOR_H
#define AUDIO_PLUGIN_EXAMPLE_OSCILLATOR_H

#include <valarray>
class Oscillator {

  public:
    double getNextSample() {
        const auto result = std::sin(d_phase);
        d_phase += 0.022;
        return result;
    }

    void reset() {
        d_phase = 0.0f;
    }

  private:
    double d_phase = 0.0f;
};

#endif // AUDIO_PLUGIN_EXAMPLE_OSCILLATOR_H
