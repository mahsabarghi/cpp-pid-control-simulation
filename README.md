# C++ PID Control System Simulation

This project demonstrates an object-oriented implementation of a discrete-time PID controller in C++, applied to a closed-loop simulation of a dynamic system.

The goal is to model and simulate control behavior in a structured and modular software architecture, similar to control-oriented software used in mechatronic systems.

---

## Architecture

The system is divided into three main components:

### 1. PIDController

- Discrete-time PID implementation (P, I, D terms)
- Configurable sampling time (dt)
- Optional output saturation (actuator limits)
- Integral clamping to prevent windup
- Encapsulated internal state

### 2. FirstOrderPlant

- Simulated dynamic system:

  dy/dt = -a*y + b*u

- Discretized using forward Euler
- Represents a simplified physical process (e.g., motor speed or temperature)

### 3. ControlLoop

- Executes closed-loop simulation
- Applies step setpoint change
- Injects disturbance
- Logs results to CSV for validation and analysis

---

## Features

- Object-oriented design with clear separation of concerns
- Discrete-time control implementation
- Anti-windup strategy
- Actuator saturation handling
- Configurable simulation parameters
- CSV-based logging for response analysis

---

## Build Instructions

```bash
cmake -S . -B build
cmake --build build -j
./build/cpp_pid_control_simulation
```

**This generates:**

```
simulation.csv
```

With columns:

```
time, setpoint, measurement, control
```

## Why This Project

This project demonstrates:

- C++ object-oriented design

- Control systems fundamentals (PID, feedback loops)

- Discrete-time simulation

- Modular system architecture

- Engineering-oriented software structure

> It reflects control-oriented development in multidisciplinary mechatronic environments.
