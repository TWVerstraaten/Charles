//
// Created by pc on 16-5-22.
//

#include "functions.h"

namespace fns {

    double modOne(double x) {
        static double dummy;
        return std::modf(x, &dummy);
    }
} // namespace fns