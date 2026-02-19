#pragma once

#include "PIDController.h"
#include "FirstOrderPlant.h"
#include <string>

struct SimulationConfig {
    double dt_seconds = 0.01;
    double duration_seconds = 6.0;

    double setpoint_initial = 0.0;
    double setpoint_step = 1.0;
    double setpoint_step_time = 1.0;

    bool enable_disturbance = true;
    double disturbance_time = 3.5;
    double disturbance_offset = -0.2;
};

class ControlLoop {
public:
    ControlLoop(PIDController controller, FirstOrderPlant plant, SimulationConfig cfg);

    // Writes CSV with columns: time,setpoint,measurement,control
    void runToCsv(const std::string& csv_path);

private:
    PIDController controller_;
    FirstOrderPlant plant_;
    SimulationConfig cfg_;
};

