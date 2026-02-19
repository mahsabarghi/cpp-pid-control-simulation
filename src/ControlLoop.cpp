#include "ControlLoop.h"
#include <fstream>
#include <iomanip>
#include <stdexcept>

ControlLoop::ControlLoop(PIDController controller, FirstOrderPlant plant, SimulationConfig cfg)
    : controller_(controller), plant_(plant), cfg_(cfg) {}

void ControlLoop::runToCsv(const std::string& csv_path) {
    std::ofstream out(csv_path);
    if (!out) {
        throw std::runtime_error("Failed to open CSV file: " + csv_path);
    }

    out << "time,setpoint,measurement,control\n";
    out << std::fixed << std::setprecision(6);

    const int steps = static_cast<int>(cfg_.duration_seconds / cfg_.dt_seconds);
    double t = 0.0;

    for (int k = 0; k <= steps; ++k) {
        const double setpoint =
            (t >= cfg_.setpoint_step_time) ? cfg_.setpoint_step : cfg_.setpoint_initial;

        double measurement = plant_.output();

        // Simulate a disturbance (e.g., sensor bias or load change)
        if (cfg_.enable_disturbance && t >= cfg_.disturbance_time) {
            measurement += cfg_.disturbance_offset;
        }

        const double u = controller_.compute(setpoint, measurement);

        // Apply control to plant
        plant_.step(u);

        out << t << "," << setpoint << "," << measurement << "," << u << "\n";
        t += cfg_.dt_seconds;
    }
}

