import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("simulation.csv")

t = df["time"].to_numpy()
r = df["setpoint"].to_numpy()
y = df["measurement"].to_numpy()

plt.figure()
plt.plot(t, r, label="Setpoint")
plt.plot(t, y, label="Measurement")
plt.xlabel("Time (s)")
plt.ylabel("Output")
plt.title("Closed-Loop Step Response")
plt.legend()
plt.grid(True)

plt.savefig("response.png", dpi=300, bbox_inches="tight")
plt.show()
