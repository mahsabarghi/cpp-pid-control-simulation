#include "FirstOrderPlant.h"
#include <stdexcept>

FirstOrderPlant::FirstOrderPlant(double a, double b, double dt_seconds, double y0)
    : a_(a), b_(b), dt_(dt_seconds), y_(y0) {
    if (dt_ <= 0.0) {
        throw std::invalid_argument("dt_seconds must be > 0");
    }
    if (a_ < 0.0) {
        throw std::invalid_argument("a must be >= 0");
    }
}

void FirstOrderPlant::setDt(double dt_seconds) {
    if (dt_seconds <= 0.0) {
        throw std::invalid_argument("dt_seconds must be > 0");
    }
    dt_ = dt_seconds;
}

void FirstOrderPlant::reset(double y0) {
    y_ = y0;
}

double FirstOrderPlant::step(double u) {
    const double dydt = (-a_ * y_) + (b_ * u);
    y_ = y_ + dt_ * dydt;
    return y_;
}

