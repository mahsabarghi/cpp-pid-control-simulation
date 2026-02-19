#pragma once

// Simple first-order dynamic system:
//   dy/dt = -a*y + b*u
// Discretized with forward Euler:
//   y[k+1] = y[k] + dt * (-a*y[k] + b*u[k])
class FirstOrderPlant {
public:
    FirstOrderPlant(double a, double b, double dt_seconds, double y0 = 0.0);

    void setDt(double dt_seconds);
    void reset(double y0 = 0.0);

    // Apply control input u for one timestep and return new output y
    double step(double u);

    double output() const { return y_; }

private:
    double a_;
    double b_;
    double dt_;
    double y_;
};

