# seismic-monitor

Real-time seismic sensor monitor with sliding window statistics written in C.

## Overview

**simulator** - generates a stream of sensor measurements with configurable frequency and burst mode.

**monitor** - reads the stream, maintains a sliding time window of recent measurements, and continuously displays statistics for each sensor.

## Simulator Options

| Flag | Type  | Description                 | Default |
|------|-------|-----------------------------|---------|
| `-n` | int   | number of sensors           | 5       |
| `-f` | float | message frequency (msg/sec) | 10.0    |
| `-b` | float | burst probability [0.0-1.0] | 0.2     |
| `-B` | int   | messages per burst          | 500     |
| `-s` | int   | random seed (0 = use time)  | 0       |

## Monitor Options

| Flag | Type | Description                         | Default |
|------|------|-------------------------------------|---------|
| `-a` | int  | sliding window size in seconds      | 30      |
| `-l` | int  | max display lag in milliseconds     | 200     |
| `-n` | int  | number of sensors                   | 5       |
| `-p` | int  | decimal places for statistics       | 2       |
| `-z` | flag | show sensors with no data in window | off     |

## Output Format

```
=== Seismic Monitor | window: 10s | lag: 200ms | 14:23:05 ===

   ID | COUNT |       MEAN |    STD DEV
 ---- | ----- | ---------- | ----------
    0 |  2524 |      -0.54 |     580.11
    1 |  2477 |       7.08 |     571.64
    2 |  2553 |     -11.01 |     574.22
    3 |  2571 |     -11.53 |     577.93
    4 |  2475 |       8.51 |     577.07
```

- **COUNT** - number of measurements currently in the sliding window
- **MEAN** - average intensity value
- **STD DEV** - standard deviation of intensity values