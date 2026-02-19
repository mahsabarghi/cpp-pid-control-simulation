#include "PIDController.h"
#include "FirstOrderPlant.h"
#include "ControlLoop.h"
#include <iostream>

int main()
{
    const double dt = 0.01; // 10 ms sampling time

    SimulationConfig cfg;
    cfg.dt_seconds = dt;
    cfg.duration_seconds = 6.0;
    cfg.setpoint_initial = 0.0;
    cfg.setpoint_step = 1.0;
    cfg.setpoint_step_time = 1.0;
    cfg.enable_disturbance = true;
    cfg.disturbance_time = 3.5;
    cfg.disturbance_offset = -0.2;

    // ---------- Run 1: Baseline (saturation + anti-windup) ----------
    {
        FirstOrderPlant plant(1.2, 1.0, dt, 0.0);
        PIDController pid(2.0, 1.0, 0.05, dt);

        pid.setOutputLimits(PIDController::Limits{-2.0, 2.0});
        pid.setIntegralLimits(PIDController::Limits{-1.0, 1.0}); // anti-windup

        ControlLoop loop(pid, plant, cfg);
        loop.runToCsv("simulation_baseline.csv");
    }

    // ---------- Run 2: No anti-windup (saturation only) ----------
    {
        FirstOrderPlant plant(1.2, 1.0, dt, 0.0);
        PIDController pid(2.0, 1.0, 0.05, dt);

        pid.setOutputLimits(PIDController::Limits{-2.0, 2.0});
        pid.setIntegralLimits(std::nullopt); // disable integral clamping

        ControlLoop loop(pid, plant, cfg);
        loop.runToCsv("simulation_no_antiwindup.csv");
    }

    std::cout << "Wrote simulation_baseline.csv and simulation_no_antiwindup.csv\n";
    return 0;
}
