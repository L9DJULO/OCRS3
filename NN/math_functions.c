#include "math_functions.h"
#include <math.h>

double sigmoid(double x) {
    return 1 / (1 + exp(-x));
}
