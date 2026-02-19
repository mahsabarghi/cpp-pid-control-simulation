import pandas as pd
import matplotlib.pyplot as plt

base = pd.read_csv("simulation_baseline.csv")
no_aw = pd.read_csv("simulation_no_antiwindup.csv")

t = base["time"].to_numpy()
r = base["setpoint"].to_numpy()

y_base = base["measurement"].to_numpy()
y_no_aw = no_aw["measurement"].to_numpy()

plt.figure()
plt.plot(t, r, label="Setpoint")
plt.plot(t, y_base, label="Measurement (baseline: anti-windup)")
plt.plot(t, y_no_aw, label="Measurement (no anti-windup)")

plt.xlabel("Time (s)")
plt.ylabel("Output")
plt.title("Closed-Loop Response: Anti-Windup vs None")
plt.legend()
plt.grid(True)
plt.axvline(x=3.5, linestyle="--", label="Disturbance (t=3.5s)")

plt.savefig("response_comparison.png", dpi=300, bbox_inches="tight")
plt.show()

