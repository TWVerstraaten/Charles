//
// Created by pc on 15-5-22.
//

#ifndef AUDIO_PLUGIN_EXAMPLE_FUNCTIONS_H
#define AUDIO_PLUGIN_EXAMPLE_FUNCTIONS_H

#include <cmath>

namespace fns {

    double modOne(double x) {
        static double dummy;
        return std::modf(x, &dummy);
    }

} // namespace fns

#endif // AUDIO_PLUGIN_EXAMPLE_FUNCTIONS_H
