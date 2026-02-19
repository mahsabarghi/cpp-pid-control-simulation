#pragma once

#include <algorithm>
#include <optional>

class PIDController
{
public:
    struct Limits
    {
        double min;
        double max;
    };

    PIDController(double kp, double ki, double kd, double dt_seconds);

    void setGains(double kp, double ki, double kd);
    void setDt(double dt_seconds);

    void setOutputLimits(std::optional<Limits> limits);
    void setIntegralLimits(std::optional<Limits> limits);

    void reset(double integral = 0.0, double previous_error = 0.0);

    double compute(double setpoint, double measurement);

private:
    double kp_;
    double ki_;
    double kd_;
    double dt_;

    double integral_;
    double previous_error_;

    std::optional<Limits> output_limits_;
    std::optional<Limits> integral_limits_;

    static double clamp(double v, const Limits &lim)
    {
        return std::max(lim.min, std::min(v, lim.max));
    }
};
