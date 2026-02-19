#include "PIDController.h"
#include <stdexcept>

PIDController::PIDController(double kp, double ki, double kd, double dt_seconds)
    : kp_(kp),
      ki_(ki),
      kd_(kd),
      dt_(dt_seconds),
      integral_(0.0),
      previous_error_(0.0),
      output_limits_(std::nullopt),
      integral_limits_(std::nullopt) {
    if (dt_ <= 0.0) {
        throw std::invalid_argument("dt_seconds must be > 0");
    }
}

void PIDController::setGains(double kp, double ki, double kd) {
    kp_ = kp;
    ki_ = ki;
    kd_ = kd;
}

void PIDController::setDt(double dt_seconds) {
    if (dt_seconds <= 0.0) {
        throw std::invalid_argument("dt_seconds must be > 0");
    }
    dt_ = dt_seconds;
}

void PIDController::setOutputLimits(std::optional<Limits> limits) {
    output_limits_ = limits;
}

void PIDController::setIntegralLimits(std::optional<Limits> limits) {
    integral_limits_ = limits;
}

void PIDController::reset(double integral, double previous_error) {
    integral_ = integral;
    previous_error_ = previous_error;
}

// Placeholder for now — we’ll implement the actual PID math next step.
double PIDController::compute(double /*setpoint*/, double /*measurement*/) {
    return 0.0;
}

