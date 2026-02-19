import pandas as pd
import numpy as np


def disturbance_recovery_metrics(
    df: pd.DataFrame,
    disturbance_time: float = 3.5,
    pre_window_s: float = 0.5,
    post_window_s: float = 2.0,
    band: float = 0.02,  # ±2% band around pre-level
) -> dict:
    """
    Computes disturbance recovery metrics around disturbance_time.

    pre_level  = median(y) in [t0 - pre_window_s, t0)
    min_after  = min(y) in [t0, t0 + post_window_s]
    drop       = pre_level - min_after
    recovery_t = first time after t0 where y enters ±band of pre_level and stays there
                until the end of the post window.
    """
    t = df["time"].to_numpy()
    y = df["measurement"].to_numpy()

    pre_mask = (t >= disturbance_time - pre_window_s) & (t < disturbance_time)
    post_mask = (t >= disturbance_time) & (t <= disturbance_time + post_window_s)

    if pre_mask.sum() < 5 or post_mask.sum() < 5:
        raise ValueError("Not enough samples around the disturbance window.")

    pre_level = float(np.median(y[pre_mask]))

    tw = t[post_mask]
    yw = y[post_mask]

    min_after = float(np.min(yw))
    drop = pre_level - min_after

    low = (1.0 - band) * pre_level
    high = (1.0 + band) * pre_level

    recovery_t = None
    for i in range(len(yw)):
        if np.all((yw[i:] >= low) & (yw[i:] <= high)):
            recovery_t = float(tw[i] - disturbance_time)
            break

    return {
        "pre_level": pre_level,
        "min_after": min_after,
        "drop": drop,
        "recovery_time_s": recovery_t,
        "band_low": low,
        "band_high": high,
    }


def fmt_time(v):
    return "n/a" if v is None else f"{v:.3f}s"


def main():
    baseline = pd.read_csv("simulation_baseline.csv")
    no_aw = pd.read_csv("simulation_no_antiwindup.csv")

    m_base = disturbance_recovery_metrics(baseline)
    m_noaw = disturbance_recovery_metrics(no_aw)

    print("--- Disturbance Recovery Metrics (t = 3.5s) ---")
    print(f"Baseline (anti-windup): pre={m_base['pre_level']:.4f}, "
          f"min={m_base['min_after']:.4f}, drop={m_base['drop']:.4f}, "
          f"recovery={fmt_time(m_base['recovery_time_s'])}")
    print(f"No anti-windup:         pre={m_noaw['pre_level']:.4f}, "
          f"min={m_noaw['min_after']:.4f}, drop={m_noaw['drop']:.4f}, "
          f"recovery={fmt_time(m_noaw['recovery_time_s'])}")


if __name__ == "__main__":
    main()
