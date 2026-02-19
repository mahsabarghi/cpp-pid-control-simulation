#include "PIDController.h"
#include "FirstOrderPlant.h"
#include "ControlLoop.h"
#include <iostream>

int main() {
    const double dt = 0.01; // 10 ms sampling time

    // Plant: dy/dt = -a*y + b*u
    FirstOrderPlant plant(/*a=*/1.2, /*b=*/1.0, dt, /*y0=*/0.0);

    // PID gains (simple starting values)
    PIDController pid(/*kp=*/2.0, /*ki=*/1.0, /*kd=*/0.05, dt);

    // Simulate actuator saturation + anti-windup
    pid.setOutputLimits(PIDController::Limits{-2.0, 2.0});
    pid.setIntegralLimits(PIDController::Limits{-1.0, 1.0});

    SimulationConfig cfg;
    cfg.dt_seconds = dt;
    cfg.duration_seconds = 6.0;
    cfg.setpoint_initial = 0.0;
    cfg.setpoint_step = 1.0;
    cfg.setpoint_step_time = 1.0;
    cfg.enable_disturbance = true;
    cfg.disturbance_time = 3.5;
    cfg.disturbance_offset = -0.2;

    ControlLoop loop(pid, plant, cfg);

    const std::string csv_path = "simulation.csv";
    loop.runToCsv(csv_path);

    std::cout << "Simulation finished. Output written to: " << csv_path << "\n";
    return 0;
}


